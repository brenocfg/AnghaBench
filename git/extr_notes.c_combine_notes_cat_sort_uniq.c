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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  struct object_id const object_id ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  blob_type ; 
 scalar_t__ for_each_string_list (struct string_list*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ string_list_add_note_lines (struct string_list*,struct object_id const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_join_lines_helper ; 
 int /*<<< orphan*/  string_list_remove_duplicates (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_remove_empty_items (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 int write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id const*) ; 

int combine_notes_cat_sort_uniq(struct object_id *cur_oid,
				const struct object_id *new_oid)
{
	struct string_list sort_uniq_list = STRING_LIST_INIT_DUP;
	struct strbuf buf = STRBUF_INIT;
	int ret = 1;

	/* read both note blob objects into unique_lines */
	if (string_list_add_note_lines(&sort_uniq_list, cur_oid))
		goto out;
	if (string_list_add_note_lines(&sort_uniq_list, new_oid))
		goto out;
	string_list_remove_empty_items(&sort_uniq_list, 0);
	string_list_sort(&sort_uniq_list);
	string_list_remove_duplicates(&sort_uniq_list, 0);

	/* create a new blob object from sort_uniq_list */
	if (for_each_string_list(&sort_uniq_list,
				 string_list_join_lines_helper, &buf))
		goto out;

	ret = write_object_file(buf.buf, buf.len, blob_type, cur_oid);

out:
	strbuf_release(&buf);
	string_list_clear(&sort_uniq_list, 0);
	return ret;
}