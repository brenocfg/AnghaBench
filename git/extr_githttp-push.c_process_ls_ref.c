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
struct remote_ls_ctx {char* dentry_name; int dentry_flags; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int IS_DIR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  one_remote_ref (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void process_ls_ref(struct remote_ls_ctx *ls)
{
	if (!strcmp(ls->path, ls->dentry_name) && (ls->dentry_flags & IS_DIR)) {
		fprintf(stderr, "  %s\n", ls->dentry_name);
		return;
	}

	if (!(ls->dentry_flags & IS_DIR))
		one_remote_ref(ls->dentry_name);
}