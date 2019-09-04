#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; size_t len; } ;
struct TYPE_6__ {TYPE_1__ map; } ;
struct TYPE_7__ {TYPE_2__ ofile; } ;
typedef  TYPE_3__ git_patch_generated ;

/* Variables and functions */

void git_patch_generated_old_data(
	char **ptr, size_t *len, git_patch_generated *patch)
{
	*ptr = patch->ofile.map.data;
	*len = patch->ofile.map.len;
}