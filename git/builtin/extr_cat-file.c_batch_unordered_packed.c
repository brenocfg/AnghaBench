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
typedef  int /*<<< orphan*/  uint32_t ;
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int batch_unordered_object (struct object_id const*,void*) ; 

__attribute__((used)) static int batch_unordered_packed(const struct object_id *oid,
				  struct packed_git *pack,
				  uint32_t pos,
				  void *data)
{
	return batch_unordered_object(oid, data);
}