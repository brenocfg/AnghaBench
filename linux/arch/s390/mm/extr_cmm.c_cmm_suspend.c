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
 int /*<<< orphan*/  cmm_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmm_page_list ; 
 int /*<<< orphan*/  cmm_pages ; 
 int cmm_suspended ; 
 int /*<<< orphan*/  cmm_timed_page_list ; 
 int /*<<< orphan*/  cmm_timed_pages ; 

__attribute__((used)) static int cmm_suspend(void)
{
	cmm_suspended = 1;
	cmm_free_pages(cmm_pages, &cmm_pages, &cmm_page_list);
	cmm_free_pages(cmm_timed_pages, &cmm_timed_pages, &cmm_timed_page_list);
	return 0;
}