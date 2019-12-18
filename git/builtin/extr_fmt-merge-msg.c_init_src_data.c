#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int strdup_strings; } ;
struct TYPE_7__ {int strdup_strings; } ;
struct TYPE_6__ {int strdup_strings; } ;
struct TYPE_5__ {int strdup_strings; } ;
struct src_data {TYPE_4__ generic; TYPE_3__ r_branch; TYPE_2__ tag; TYPE_1__ branch; } ;

/* Variables and functions */

__attribute__((used)) static void init_src_data(struct src_data *data)
{
	data->branch.strdup_strings = 1;
	data->tag.strdup_strings = 1;
	data->r_branch.strdup_strings = 1;
	data->generic.strdup_strings = 1;
}