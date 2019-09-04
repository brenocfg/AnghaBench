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
struct collision_entry {int /*<<< orphan*/  target_file; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int collision_cmp(void *unused_cmp_data,
			 const struct collision_entry *e1,
			 const struct collision_entry *e2,
			 const void *unused_keydata)
{
	return strcmp(e1->target_file, e2->target_file);
}