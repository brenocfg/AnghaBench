#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {TYPE_2__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 TYPE_3__* DELTA (struct object_entry*) ; 
 unsigned long DELTA_SIZE (struct object_entry*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 void* diff_delta (void*,unsigned long,void*,unsigned long,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 

__attribute__((used)) static void *get_delta(struct object_entry *entry)
{
	unsigned long size, base_size, delta_size;
	void *buf, *base_buf, *delta_buf;
	enum object_type type;

	buf = read_object_file(&entry->idx.oid, &type, &size);
	if (!buf)
		die(_("unable to read %s"), oid_to_hex(&entry->idx.oid));
	base_buf = read_object_file(&DELTA(entry)->idx.oid, &type,
				    &base_size);
	if (!base_buf)
		die("unable to read %s",
		    oid_to_hex(&DELTA(entry)->idx.oid));
	delta_buf = diff_delta(base_buf, base_size,
			       buf, size, &delta_size, 0);
	/*
	 * We succesfully computed this delta once but dropped it for
	 * memory reasons. Something is very wrong if this time we
	 * recompute and create a different delta.
	 */
	if (!delta_buf || delta_size != DELTA_SIZE(entry))
		BUG("delta size changed");
	free(buf);
	free(base_buf);
	return delta_buf;
}