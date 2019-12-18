#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* lw_list; int /*<<< orphan*/  lw_err; } ;
typedef  TYPE_1__ linkwalk_t ;
struct TYPE_5__ {struct TYPE_5__* lnl_next; int /*<<< orphan*/  linkname; } ;
typedef  TYPE_2__ linknamelist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DLPI_LINKNAME_MAX ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
list_interfaces(const char *linkname, void *arg)
{
	linkwalk_t	*lwp = arg;
	linknamelist_t	*entry;

	if ((entry = calloc(1, sizeof(linknamelist_t))) == NULL) {
		lwp->lw_err = ENOMEM;
		return (B_TRUE);
	}
	(void) strlcpy(entry->linkname, linkname, DLPI_LINKNAME_MAX);

	if (lwp->lw_list == NULL) {
		lwp->lw_list = entry;
	} else {
		entry->lnl_next = lwp->lw_list;
		lwp->lw_list = entry;
	}

	return (B_FALSE);
}