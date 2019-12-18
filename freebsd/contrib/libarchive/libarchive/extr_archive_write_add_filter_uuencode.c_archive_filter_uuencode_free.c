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
struct private_uuencode {int /*<<< orphan*/  encoded_buff; int /*<<< orphan*/  name; } ;
struct archive_write_filter {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct private_uuencode*) ; 

__attribute__((used)) static int
archive_filter_uuencode_free(struct archive_write_filter *f)
{
	struct private_uuencode *state = (struct private_uuencode *)f->data;

	archive_string_free(&state->name);
	archive_string_free(&state->encoded_buff);
	free(state);
	return (ARCHIVE_OK);
}