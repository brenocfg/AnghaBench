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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct object {struct object_id oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 char* find_unique_abbrev (struct object_id const*,int /*<<< orphan*/ ) ; 
 char* get_rev_name (struct object const*,struct strbuf*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_name(const struct object *obj,
		      const char *caller_name,
		      int always, int allow_undefined, int name_only)
{
	const char *name;
	const struct object_id *oid = &obj->oid;
	struct strbuf buf = STRBUF_INIT;

	if (!name_only)
		printf("%s ", caller_name ? caller_name : oid_to_hex(oid));
	name = get_rev_name(obj, &buf);
	if (name)
		printf("%s\n", name);
	else if (allow_undefined)
		printf("undefined\n");
	else if (always)
		printf("%s\n", find_unique_abbrev(oid, DEFAULT_ABBREV));
	else
		die("cannot describe '%s'", oid_to_hex(oid));
	strbuf_release(&buf);
}