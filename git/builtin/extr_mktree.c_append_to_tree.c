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
struct treeent {unsigned int mode; size_t len; int /*<<< orphan*/  oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct treeent**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct treeent*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 struct treeent** entries ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ strchr (char*,char) ; 
 size_t strlen (char*) ; 
 scalar_t__ used ; 

__attribute__((used)) static void append_to_tree(unsigned mode, struct object_id *oid, char *path)
{
	struct treeent *ent;
	size_t len = strlen(path);
	if (strchr(path, '/'))
		die("path %s contains slash", path);

	FLEX_ALLOC_MEM(ent, name, path, len);
	ent->mode = mode;
	ent->len = len;
	oidcpy(&ent->oid, oid);

	ALLOC_GROW(entries, used + 1, alloc);
	entries[used++] = ent;
}