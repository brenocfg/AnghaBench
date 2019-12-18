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

/* Variables and functions */
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_dummy_ref(const char *line)
{
	struct object_id oid;
	const char *name;

	if (parse_oid_hex(line, &oid, &name))
		return 0;
	if (*name != ' ')
		return 0;
	name++;

	return oideq(&null_oid, &oid) && !strcmp(name, "capabilities^{}");
}