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
struct object_id {int dummy; } ;
struct bitmap_index {int dummy; } ;

/* Variables and functions */
 int bitmap_position_extended (struct bitmap_index*,struct object_id const*) ; 
 int bitmap_position_packfile (struct bitmap_index*,struct object_id const*) ; 

__attribute__((used)) static int bitmap_position(struct bitmap_index *bitmap_git,
			   const struct object_id *oid)
{
	int pos = bitmap_position_packfile(bitmap_git, oid);
	return (pos >= 0) ? pos : bitmap_position_extended(bitmap_git, oid);
}