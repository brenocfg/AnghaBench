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
struct TYPE_2__ {int offset; int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; scalar_t__ preferred_base; } ;
struct hashfile {int dummy; } ;
typedef  int off_t ;
typedef  enum write_one_status { ____Placeholder_write_one_status } write_one_status ;

/* Variables and functions */
 struct object_entry* DELTA (struct object_entry*) ; 
 int /*<<< orphan*/  SET_DELTA (struct object_entry*,int /*<<< orphan*/ *) ; 
#define  WRITE_ONE_BREAK 129 
#define  WRITE_ONE_RECURSIVE 128 
 int WRITE_ONE_SKIP ; 
 int WRITE_ONE_WRITTEN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_written ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ signed_add_overflows (int,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_object (struct hashfile*,struct object_entry*,int) ; 
 TYPE_1__** written_list ; 

__attribute__((used)) static enum write_one_status write_one(struct hashfile *f,
				       struct object_entry *e,
				       off_t *offset)
{
	off_t size;
	int recursing;

	/*
	 * we set offset to 1 (which is an impossible value) to mark
	 * the fact that this object is involved in "write its base
	 * first before writing a deltified object" recursion.
	 */
	recursing = (e->idx.offset == 1);
	if (recursing) {
		warning(_("recursive delta detected for object %s"),
			oid_to_hex(&e->idx.oid));
		return WRITE_ONE_RECURSIVE;
	} else if (e->idx.offset || e->preferred_base) {
		/* offset is non zero if object is written already. */
		return WRITE_ONE_SKIP;
	}

	/* if we are deltified, write out base object first. */
	if (DELTA(e)) {
		e->idx.offset = 1; /* now recurse */
		switch (write_one(f, DELTA(e), offset)) {
		case WRITE_ONE_RECURSIVE:
			/* we cannot depend on this one */
			SET_DELTA(e, NULL);
			break;
		default:
			break;
		case WRITE_ONE_BREAK:
			e->idx.offset = recursing;
			return WRITE_ONE_BREAK;
		}
	}

	e->idx.offset = *offset;
	size = write_object(f, e, *offset);
	if (!size) {
		e->idx.offset = recursing;
		return WRITE_ONE_BREAK;
	}
	written_list[nr_written++] = &e->idx;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(*offset, size))
		die(_("pack too large for current definition of off_t"));
	*offset += size;
	return WRITE_ONE_WRITTEN;
}