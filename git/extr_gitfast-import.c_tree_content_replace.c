#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct tree_entry {struct tree_content* tree; TYPE_1__* versions; } ;
struct tree_content {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  release_tree_content_recursive (struct tree_content*) ; 

__attribute__((used)) static void tree_content_replace(
	struct tree_entry *root,
	const struct object_id *oid,
	const uint16_t mode,
	struct tree_content *newtree)
{
	if (!S_ISDIR(mode))
		die("Root cannot be a non-directory");
	oidclr(&root->versions[0].oid);
	oidcpy(&root->versions[1].oid, oid);
	if (root->tree)
		release_tree_content_recursive(root->tree);
	root->tree = newtree;
}