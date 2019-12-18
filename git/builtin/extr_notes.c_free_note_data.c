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
struct note_data {int /*<<< orphan*/  buf; scalar_t__ edit_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_or_warn (scalar_t__) ; 

__attribute__((used)) static void free_note_data(struct note_data *d)
{
	if (d->edit_path) {
		unlink_or_warn(d->edit_path);
		free(d->edit_path);
	}
	strbuf_release(&d->buf);
}