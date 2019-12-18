#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
struct acpi_walk_state {int /*<<< orphan*/  opcode; TYPE_3__* op_info; TYPE_2__* method_node; TYPE_4__* method_desc; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_10__ {int info_flags; scalar_t__ sync_level; } ;
struct TYPE_9__ {TYPE_5__ method; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  ascii; } ;
struct TYPE_7__ {TYPE_1__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/  (*) (struct acpi_walk_state*,union acpi_parse_object**)) ; 
 int ACPI_METHOD_IGNORE_SYNC_LEVEL ; 
 int ACPI_METHOD_SERIALIZED ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int AML_CREATE ; 
 int AML_FIELD ; 
 int AML_NAMED ; 

__attribute__((used)) static acpi_status
acpi_ds_detect_named_opcodes(struct acpi_walk_state *walk_state,
			     union acpi_parse_object **out_op)
{

	ACPI_FUNCTION_NAME(acpi_ds_detect_named_opcodes);

	/* We are only interested in opcodes that create a new name */

	if (!
	    (walk_state->op_info->
	     flags & (AML_NAMED | AML_CREATE | AML_FIELD))) {
		return (AE_OK);
	}

	/*
	 * At this point, we know we have a Named object opcode.
	 * Mark the method as serialized. Later code will create a mutex for
	 * this method to enforce serialization.
	 *
	 * Note, ACPI_METHOD_IGNORE_SYNC_LEVEL flag means that we will ignore the
	 * Sync Level mechanism for this method, even though it is now serialized.
	 * Otherwise, there can be conflicts with existing ASL code that actually
	 * uses sync levels.
	 */
	walk_state->method_desc->method.sync_level = 0;
	walk_state->method_desc->method.info_flags |=
	    (ACPI_METHOD_SERIALIZED | ACPI_METHOD_IGNORE_SYNC_LEVEL);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Method serialized [%4.4s] %p - [%s] (%4.4X)\n",
			  walk_state->method_node->name.ascii,
			  walk_state->method_node, walk_state->op_info->name,
			  walk_state->opcode));

	/* Abort the parse, no need to examine this method any further */

	return (AE_CTRL_TERMINATE);
}