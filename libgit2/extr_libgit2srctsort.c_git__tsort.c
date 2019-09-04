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
typedef  int /*<<< orphan*/  git__tsort_cmp ;

/* Variables and functions */
 int /*<<< orphan*/  git__tsort_r (void**,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsort_r_cmp ; 

void git__tsort(void **dst, size_t size, git__tsort_cmp cmp)
{
	git__tsort_r(dst, size, tsort_r_cmp, cmp);
}