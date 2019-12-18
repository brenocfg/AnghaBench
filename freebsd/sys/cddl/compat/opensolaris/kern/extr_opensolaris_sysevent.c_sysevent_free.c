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
struct sysevent {int /*<<< orphan*/ * se_nvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct sysevent*,int) ; 
 int /*<<< orphan*/  sysevent_free_attr (int /*<<< orphan*/ *) ; 

void
sysevent_free(sysevent_t *evp)
{
	struct sysevent *ev = (struct sysevent *)evp;

	ASSERT(evp != NULL);

	if (ev->se_nvl != NULL)
		sysevent_free_attr(ev->se_nvl);
	kmem_free(ev, sizeof(*ev));
}