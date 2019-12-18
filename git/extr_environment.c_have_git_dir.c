#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ have_repository; } ;
struct TYPE_3__ {scalar_t__ gitdir; } ;

/* Variables and functions */
 TYPE_2__* startup_info ; 
 TYPE_1__* the_repository ; 

int have_git_dir(void)
{
	return startup_info->have_repository
		|| the_repository->gitdir;
}