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
 int /*<<< orphan*/  mark_object_for_connectivity (struct object_id const*) ; 

__attribute__((used)) static int mark_packed_for_connectivity(const struct object_id *oid,
					struct packed_git *pack,
					uint32_t pos,
					void *data)
{
	mark_object_for_connectivity(oid);
	return 0;
}