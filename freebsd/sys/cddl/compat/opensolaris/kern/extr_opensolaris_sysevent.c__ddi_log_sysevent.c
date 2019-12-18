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
typedef  int /*<<< orphan*/  sysevent_t ;
typedef  int /*<<< orphan*/  sysevent_id_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDI_SLEEP ; 
 int /*<<< orphan*/  SE_SLEEP ; 
 int log_sysevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sysevent_alloc (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysevent_attach_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysevent_detach_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysevent_free (int /*<<< orphan*/ *) ; 

int
_ddi_log_sysevent(char *vendor, char *class, char *subclass,
    nvlist_t *attr_list, sysevent_id_t *eidp, int flag)
{
	sysevent_t *ev;
	int ret;

	ASSERT(vendor != NULL);
	ASSERT(class != NULL);
	ASSERT(subclass != NULL);
	ASSERT(attr_list != NULL);
	ASSERT(eidp != NULL);
	ASSERT(flag == DDI_SLEEP);

	ev = sysevent_alloc(class, subclass, vendor, SE_SLEEP);
	ASSERT(ev != NULL);
	(void)sysevent_attach_attributes(ev, attr_list);
        ret = log_sysevent(ev, SE_SLEEP, eidp);
	sysevent_detach_attributes(ev);
	sysevent_free(ev);

	return (ret);
}