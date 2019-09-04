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
struct string_list_item {struct src_data* util; } ;
struct src_data {int head_status; int is_local_branch; int /*<<< orphan*/  generic; int /*<<< orphan*/  r_branch; int /*<<< orphan*/  tag; int /*<<< orphan*/  branch; int /*<<< orphan*/  oid; } ;
struct origin_data {int head_status; int is_local_branch; int /*<<< orphan*/  generic; int /*<<< orphan*/  r_branch; int /*<<< orphan*/  tag; int /*<<< orphan*/  branch; int /*<<< orphan*/  oid; } ;
struct object_id {int dummy; } ;
struct merge_parents {int dummy; } ;
struct TYPE_2__ {unsigned int hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_merge_parent (struct merge_parents*,struct object_id*,int /*<<< orphan*/ *) ; 
 int get_oid_hex (char*,struct object_id*) ; 
 int /*<<< orphan*/  init_src_data (struct src_data*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  origins ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 int /*<<< orphan*/  srcs ; 
 scalar_t__ starts_with (char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 struct string_list_item* string_list_append (int /*<<< orphan*/ *,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char*) ; 
 TYPE_1__* the_hash_algo ; 
 struct string_list_item* unsorted_string_list_lookup (int /*<<< orphan*/ *,char*) ; 
 void* xcalloc (int,int) ; 
 char* xmemdupz (char const*,int) ; 
 char* xstrfmt (char*,char const*,char*) ; 

__attribute__((used)) static int handle_line(char *line, struct merge_parents *merge_parents)
{
	int i, len = strlen(line);
	struct origin_data *origin_data;
	char *src;
	const char *origin;
	struct src_data *src_data;
	struct string_list_item *item;
	int pulling_head = 0;
	struct object_id oid;
	const unsigned hexsz = the_hash_algo->hexsz;

	if (len < hexsz + 3 || line[hexsz] != '\t')
		return 1;

	if (starts_with(line + hexsz + 1, "not-for-merge"))
		return 0;

	if (line[hexsz + 1] != '\t')
		return 2;

	i = get_oid_hex(line, &oid);
	if (i)
		return 3;

	if (!find_merge_parent(merge_parents, &oid, NULL))
		return 0; /* subsumed by other parents */

	origin_data = xcalloc(1, sizeof(struct origin_data));
	oidcpy(&origin_data->oid, &oid);

	if (line[len - 1] == '\n')
		line[len - 1] = 0;
	line += hexsz + 2;

	/*
	 * At this point, line points at the beginning of comment e.g.
	 * "branch 'frotz' of git://that/repository.git".
	 * Find the repository name and point it with src.
	 */
	src = strstr(line, " of ");
	if (src) {
		*src = 0;
		src += 4;
		pulling_head = 0;
	} else {
		src = line;
		pulling_head = 1;
	}

	item = unsorted_string_list_lookup(&srcs, src);
	if (!item) {
		item = string_list_append(&srcs, src);
		item->util = xcalloc(1, sizeof(struct src_data));
		init_src_data(item->util);
	}
	src_data = item->util;

	if (pulling_head) {
		origin = src;
		src_data->head_status |= 1;
	} else if (starts_with(line, "branch ")) {
		origin_data->is_local_branch = 1;
		origin = line + 7;
		string_list_append(&src_data->branch, origin);
		src_data->head_status |= 2;
	} else if (starts_with(line, "tag ")) {
		origin = line;
		string_list_append(&src_data->tag, origin + 4);
		src_data->head_status |= 2;
	} else if (skip_prefix(line, "remote-tracking branch ", &origin)) {
		string_list_append(&src_data->r_branch, origin);
		src_data->head_status |= 2;
	} else {
		origin = src;
		string_list_append(&src_data->generic, line);
		src_data->head_status |= 2;
	}

	if (!strcmp(".", src) || !strcmp(src, origin)) {
		int len = strlen(origin);
		if (origin[0] == '\'' && origin[len - 1] == '\'')
			origin = xmemdupz(origin + 1, len - 2);
	} else
		origin = xstrfmt("%s of %s", origin, src);
	if (strcmp(".", src))
		origin_data->is_local_branch = 0;
	string_list_append(&origins, origin)->util = origin_data;
	return 0;
}