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
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 

__attribute__((used)) static int append_oid_to_argv(const struct object_id *oid, void *data)
{
	struct argv_array *argv = data;
	argv_array_push(argv, oid_to_hex(oid));
	return 0;
}