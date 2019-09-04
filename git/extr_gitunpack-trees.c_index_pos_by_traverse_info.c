#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unpack_trees_options {TYPE_2__* src_index; } ;
struct traverse_info {struct unpack_trees_options* data; } ;
struct name_entry {int dummy; } ;
struct TYPE_4__ {TYPE_1__** cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int index_name_pos (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  make_traverse_path (char*,struct traverse_info*,struct name_entry*) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int traverse_path_len (struct traverse_info*,struct name_entry*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static int index_pos_by_traverse_info(struct name_entry *names,
				      struct traverse_info *info)
{
	struct unpack_trees_options *o = info->data;
	int len = traverse_path_len(info, names);
	char *name = xmalloc(len + 1 /* slash */ + 1 /* NUL */);
	int pos;

	make_traverse_path(name, info, names);
	name[len++] = '/';
	name[len] = '\0';
	pos = index_name_pos(o->src_index, name, len);
	if (pos >= 0)
		BUG("This is a directory and should not exist in index");
	pos = -pos - 1;
	if (!starts_with(o->src_index->cache[pos]->name, name) ||
	    (pos > 0 && starts_with(o->src_index->cache[pos-1]->name, name)))
		BUG("pos must point at the first entry in this directory");
	free(name);
	return pos;
}