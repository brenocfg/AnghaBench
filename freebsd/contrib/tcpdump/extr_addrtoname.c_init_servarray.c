#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct servent {char* s_name; int /*<<< orphan*/  s_proto; int /*<<< orphan*/  s_port; } ;
struct hnamemem {int addr; struct hnamemem* nxt; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;scalar_t__ ndo_nflag; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 int /*<<< orphan*/  endservent () ; 
 struct servent* getservent () ; 
 struct hnamemem* newhnamemem (TYPE_1__*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 struct hnamemem* tporttable ; 
 struct hnamemem* uporttable ; 

__attribute__((used)) static void
init_servarray(netdissect_options *ndo)
{
	struct servent *sv;
	register struct hnamemem *table;
	register int i;
	char buf[sizeof("0000000000")];

	while ((sv = getservent()) != NULL) {
		int port = ntohs(sv->s_port);
		i = port & (HASHNAMESIZE-1);
		if (strcmp(sv->s_proto, "tcp") == 0)
			table = &tporttable[i];
		else if (strcmp(sv->s_proto, "udp") == 0)
			table = &uporttable[i];
		else
			continue;

		while (table->name)
			table = table->nxt;
		if (ndo->ndo_nflag) {
			(void)snprintf(buf, sizeof(buf), "%d", port);
			table->name = strdup(buf);
		} else
			table->name = strdup(sv->s_name);
		if (table->name == NULL)
			(*ndo->ndo_error)(ndo, "init_servarray: strdup");

		table->addr = port;
		table->nxt = newhnamemem(ndo);
	}
	endservent();
}