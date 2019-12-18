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
typedef  int /*<<< orphan*/  linux_shared_page_obj ;
typedef  int /*<<< orphan*/  __elfN ;

/* Variables and functions */
 int /*<<< orphan*/  LIN_SDT_PROBE0 (int /*<<< orphan*/ ,void (*) (void const*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysvec ; 
 int /*<<< orphan*/  todo ; 

__attribute__((used)) static void
linux_vdso_deinstall(const void *param)
{

	LIN_SDT_PROBE0(sysvec, linux_vdso_deinstall, todo);
	__elfN(linux_shared_page_fini)(linux_shared_page_obj);
}