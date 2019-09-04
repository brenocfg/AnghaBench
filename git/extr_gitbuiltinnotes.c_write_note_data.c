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
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct note_data {scalar_t__ edit_path; TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  blob_type ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static void write_note_data(struct note_data *d, struct object_id *oid)
{
	if (write_object_file(d->buf.buf, d->buf.len, blob_type, oid)) {
		error(_("unable to write note object"));
		if (d->edit_path)
			error(_("the note contents have been left in %s"),
				d->edit_path);
		exit(128);
	}
}