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
struct snmp_toolinfo {int /*<<< orphan*/  filelist; } ;
struct fname {struct fname* name; } ;

/* Variables and functions */
 struct fname* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fname*) ; 
 int /*<<< orphan*/  link ; 

void
free_filelist(struct snmp_toolinfo *snmptoolctx)
{
	struct fname *f;

	if (snmptoolctx == NULL)
		return; /* XXX error handling */

	while ((f = SLIST_FIRST(&snmptoolctx->filelist)) != NULL) {
		SLIST_REMOVE_HEAD(&snmptoolctx->filelist, link);
		if (f->name)
			free(f->name);
		free(f);
	}
}