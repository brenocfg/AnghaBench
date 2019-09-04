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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 void* read_object_file_extended (struct repository*,struct object_id const*,int*,unsigned long*,int) ; 

__attribute__((used)) static inline void *repo_read_object_file(struct repository *r,
					  const struct object_id *oid,
					  enum object_type *type,
					  unsigned long *size)
{
	return read_object_file_extended(r, oid, type, size, 1);
}