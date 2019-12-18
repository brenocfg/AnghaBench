#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* orig_head_name; } ;
typedef  TYPE_1__ git_rebase ;

/* Variables and functions */

const char *git_rebase_orig_head_name(git_rebase *rebase) {
	return rebase->orig_head_name;
}