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
struct write_each_note_data {int /*<<< orphan*/  root; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 size_t FANOUT_PATH_SEPARATORS ; 
 size_t GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t strlen (char*) ; 
 scalar_t__ write_each_non_note_until (char*,struct write_each_note_data*) ; 
 scalar_t__ write_each_note_helper (int /*<<< orphan*/ ,char*,unsigned int,struct object_id const*) ; 

__attribute__((used)) static int write_each_note(const struct object_id *object_oid,
		const struct object_id *note_oid, char *note_path,
		void *cb_data)
{
	struct write_each_note_data *d =
		(struct write_each_note_data *) cb_data;
	size_t note_path_len = strlen(note_path);
	unsigned int mode = 0100644;

	if (note_path[note_path_len - 1] == '/') {
		/* subtree entry */
		note_path_len--;
		note_path[note_path_len] = '\0';
		mode = 040000;
	}
	assert(note_path_len <= GIT_MAX_HEXSZ + FANOUT_PATH_SEPARATORS);

	/* Weave non-note entries into note entries */
	return  write_each_non_note_until(note_path, d) ||
		write_each_note_helper(d->root, note_path, mode, note_oid);
}