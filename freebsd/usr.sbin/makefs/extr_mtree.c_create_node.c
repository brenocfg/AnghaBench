#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  contents; int /*<<< orphan*/  symlink; TYPE_3__* inode; struct TYPE_9__* parent; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ fsnode ;
struct TYPE_8__ {int st_mode; } ;
struct TYPE_10__ {TYPE_1__ st; } ;

/* Variables and functions */
 int S_IFLNK ; 
 int S_IFMT ; 
 int S_IFREG ; 
 void* ecalloc (int,int) ; 
 int /*<<< orphan*/  estrdup (char const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static fsnode *
create_node(const char *name, u_int type, fsnode *parent, fsnode *global)
{
	fsnode *n;

	n = ecalloc(1, sizeof(*n));
	n->name = estrdup(name);
	n->type = (type == 0) ? global->type : type;
	n->parent = parent;

	n->inode = ecalloc(1, sizeof(*n->inode));

	/* Assign global options/defaults. */
	memcpy(n->inode, global->inode, sizeof(*n->inode));
	n->inode->st.st_mode = (n->inode->st.st_mode & ~S_IFMT) | n->type;

	if (n->type == S_IFLNK)
		n->symlink = global->symlink;
	else if (n->type == S_IFREG)
		n->contents = global->contents;

	return (n);
}