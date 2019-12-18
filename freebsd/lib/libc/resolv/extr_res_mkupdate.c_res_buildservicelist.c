#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct valuelist {struct valuelist* prev; struct valuelist* next; int /*<<< orphan*/  port; struct valuelist* proto; struct valuelist* name; } ;
struct servent {scalar_t__ s_port; int /*<<< orphan*/  s_proto; int /*<<< orphan*/  s_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  endservent () ; 
 int /*<<< orphan*/  free (struct valuelist*) ; 
 struct servent* getservent () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct valuelist* servicelist ; 
 int /*<<< orphan*/  setservent (int) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
res_buildservicelist(void) {
	struct servent *sp;
	struct valuelist *slp;

#ifdef MAYBE_HESIOD
	setservent(0);
#else
	setservent(1);
#endif
	while ((sp = getservent()) != NULL) {
		slp = (struct valuelist *)malloc(sizeof(struct valuelist));
		if (!slp)
			break;
		slp->name = strdup(sp->s_name);
		slp->proto = strdup(sp->s_proto);
		if ((slp->name == NULL) || (slp->proto == NULL)) {
			if (slp->name) free(slp->name);
			if (slp->proto) free(slp->proto);
			free(slp);
			break;
		}
		slp->port = ntohs((u_int16_t)sp->s_port);  /*%< host byt order */
		slp->next = servicelist;
		slp->prev = NULL;
		if (servicelist)
			servicelist->prev = slp;
		servicelist = slp;
	}
	endservent();
}