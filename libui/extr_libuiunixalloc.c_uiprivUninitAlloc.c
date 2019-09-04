#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* allocations ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_ptr_array_foreach (TYPE_1__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivUserBug (char*,char*) ; 
 int /*<<< orphan*/  uninitComplain ; 

void uiprivUninitAlloc(void)
{
	char *str = NULL;

	if (allocations->len == 0) {
		g_ptr_array_free(allocations, TRUE);
		return;
	}
	g_ptr_array_foreach(allocations, uninitComplain, &str);
	uiprivUserBug("Some data was leaked; either you left a uiControl lying around or there's a bug in libui itself. Leaked data:\n%s", str);
	g_free(str);
}