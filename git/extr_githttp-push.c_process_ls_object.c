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
struct remote_ls_ctx {char* dentry_name; int flags; int /*<<< orphan*/  path; scalar_t__ userData; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int IS_DIR ; 
 scalar_t__ get_oid_hex_from_objpath (char const*,struct object_id*) ; 
 int /*<<< orphan*/  one_remote_object (struct object_id*) ; 
 int* remote_dir_exists ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void process_ls_object(struct remote_ls_ctx *ls)
{
	unsigned int *parent = (unsigned int *)ls->userData;
	const char *path = ls->dentry_name;
	struct object_id oid;

	if (!strcmp(ls->path, ls->dentry_name) && (ls->flags & IS_DIR)) {
		remote_dir_exists[*parent] = 1;
		return;
	}

	if (!skip_prefix(path, "objects/", &path) ||
	    get_oid_hex_from_objpath(path, &oid))
		return;

	one_remote_object(&oid);
}