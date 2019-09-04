#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int strdup_strings; } ;
struct reflog_walk_info {TYPE_1__ complete_reflogs; } ;

/* Variables and functions */
 struct reflog_walk_info* xcalloc (int,int) ; 

void init_reflog_walk(struct reflog_walk_info **info)
{
	*info = xcalloc(1, sizeof(struct reflog_walk_info));
	(*info)->complete_reflogs.strdup_strings = 1;
}