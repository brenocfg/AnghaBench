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

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_global_ctrls_list ; 
 int /*<<< orphan*/  fst_global_groups_list ; 
 int fst_global_initialized ; 
 int /*<<< orphan*/  fst_session_global_init () ; 

int fst_global_init(void)
{
	dl_list_init(&fst_global_groups_list);
	dl_list_init(&fst_global_ctrls_list);
	fst_session_global_init();
	fst_global_initialized = 1;
	return 0;
}