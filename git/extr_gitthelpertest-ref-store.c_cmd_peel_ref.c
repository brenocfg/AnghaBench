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
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int refs_peel_ref (struct ref_store*,char const*,struct object_id*) ; 

__attribute__((used)) static int cmd_peel_ref(struct ref_store *refs, const char **argv)
{
	const char *refname = notnull(*argv++, "refname");
	struct object_id oid;
	int ret;

	ret = refs_peel_ref(refs, refname, &oid);
	if (!ret)
		puts(oid_to_hex(&oid));
	return ret;
}