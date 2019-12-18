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
struct object {int /*<<< orphan*/  oid; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_commit_oid ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* type_name (scalar_t__) ; 

__attribute__((used)) static void report_missing(const struct object *obj)
{
	fprintf(stderr, "Cannot obtain needed %s %s\n",
		obj->type ? type_name(obj->type): "object",
		oid_to_hex(&obj->oid));
	if (!is_null_oid(&current_commit_oid))
		fprintf(stderr, "while processing commit %s.\n",
			oid_to_hex(&current_commit_oid));
}