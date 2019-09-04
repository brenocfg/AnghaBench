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
 int /*<<< orphan*/  add_loose_object ; 
 int /*<<< orphan*/  for_each_loose_file_in_objdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object_directory () ; 

__attribute__((used)) static void add_unreachable_loose_objects(void)
{
	for_each_loose_file_in_objdir(get_object_directory(),
				      add_loose_object,
				      NULL, NULL, NULL);
}