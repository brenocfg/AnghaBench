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
struct delta_info {unsigned long size; unsigned int nr; struct delta_info* next; void* delta; int /*<<< orphan*/  base_offset; int /*<<< orphan*/  base_oid; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 struct delta_info* delta_list ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 struct delta_info* xmalloc (int) ; 

__attribute__((used)) static void add_delta_to_list(unsigned nr, const struct object_id *base_oid,
			      off_t base_offset,
			      void *delta, unsigned long size)
{
	struct delta_info *info = xmalloc(sizeof(*info));

	oidcpy(&info->base_oid, base_oid);
	info->base_offset = base_offset;
	info->size = size;
	info->delta = delta;
	info->nr = nr;
	info->next = delta_list;
	delta_list = info;
}