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
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static int parse_have(const char *line, struct oid_array *haves)
{
	const char *arg;
	if (skip_prefix(line, "have ", &arg)) {
		struct object_id oid;

		if (get_oid_hex(arg, &oid))
			die("git upload-pack: expected SHA1 object, got '%s'", arg);
		oid_array_append(haves, &oid);
		return 1;
	}

	return 0;
}