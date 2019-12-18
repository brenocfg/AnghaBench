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
struct tffs_key_name_table {int size; TYPE_1__* entries; } ;
struct TYPE_2__ {char* val; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void show_all_key_names(struct tffs_key_name_table *key_names)
{
	int i;

	for (i = 0; i < key_names->size; i++)
		printf("%s\n", key_names->entries[i].val);
}