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
struct traverse_info {int dummy; } ;
struct name_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_name_entry (int,struct name_entry*) ; 
 int /*<<< orphan*/  debug_path (struct traverse_info*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void debug_unpack_callback(int n,
				  unsigned long mask,
				  unsigned long dirmask,
				  struct name_entry *names,
				  struct traverse_info *info)
{
	int i;
	printf("* unpack mask %lu, dirmask %lu, cnt %d ",
	       mask, dirmask, n);
	debug_path(info);
	putchar('\n');
	for (i = 0; i < n; i++)
		debug_name_entry(i, names + i);
}