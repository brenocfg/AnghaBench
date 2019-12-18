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
struct push_info {struct push_info* dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct push_info*) ; 

__attribute__((used)) static void clear_push_info(void *util, const char *string)
{
	struct push_info *info = util;
	free(info->dest);
	free(info);
}