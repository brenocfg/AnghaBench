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
struct snapshot_record {char const* start; int len; } ;
struct snapshot {char* start; char* eof; char* buf; TYPE_1__* refs; } ;
struct TYPE_4__ {int hexsz; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct snapshot_record*,size_t,size_t) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  QSORT (struct snapshot_record*,size_t,scalar_t__ (*) (struct snapshot_record*,struct snapshot_record*)) ; 
 int /*<<< orphan*/  clear_snapshot_buffer (struct snapshot*) ; 
 scalar_t__ cmp_packed_ref_records (struct snapshot_record*,struct snapshot_record*) ; 
 int /*<<< orphan*/  die_invalid_line (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  free (struct snapshot_record*) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_2__* the_hash_algo ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void sort_snapshot(struct snapshot *snapshot)
{
	struct snapshot_record *records = NULL;
	size_t alloc = 0, nr = 0;
	int sorted = 1;
	const char *pos, *eof, *eol;
	size_t len, i;
	char *new_buffer, *dst;

	pos = snapshot->start;
	eof = snapshot->eof;

	if (pos == eof)
		return;

	len = eof - pos;

	/*
	 * Initialize records based on a crude estimate of the number
	 * of references in the file (we'll grow it below if needed):
	 */
	ALLOC_GROW(records, len / 80 + 20, alloc);

	while (pos < eof) {
		eol = memchr(pos, '\n', eof - pos);
		if (!eol)
			/* The safety check should prevent this. */
			BUG("unterminated line found in packed-refs");
		if (eol - pos < the_hash_algo->hexsz + 2)
			die_invalid_line(snapshot->refs->path,
					 pos, eof - pos);
		eol++;
		if (eol < eof && *eol == '^') {
			/*
			 * Keep any peeled line together with its
			 * reference:
			 */
			const char *peeled_start = eol;

			eol = memchr(peeled_start, '\n', eof - peeled_start);
			if (!eol)
				/* The safety check should prevent this. */
				BUG("unterminated peeled line found in packed-refs");
			eol++;
		}

		ALLOC_GROW(records, nr + 1, alloc);
		records[nr].start = pos;
		records[nr].len = eol - pos;
		nr++;

		if (sorted &&
		    nr > 1 &&
		    cmp_packed_ref_records(&records[nr - 2],
					   &records[nr - 1]) >= 0)
			sorted = 0;

		pos = eol;
	}

	if (sorted)
		goto cleanup;

	/* We need to sort the memory. First we sort the records array: */
	QSORT(records, nr, cmp_packed_ref_records);

	/*
	 * Allocate a new chunk of memory, and copy the old memory to
	 * the new in the order indicated by `records` (not bothering
	 * with the header line):
	 */
	new_buffer = xmalloc(len);
	for (dst = new_buffer, i = 0; i < nr; i++) {
		memcpy(dst, records[i].start, records[i].len);
		dst += records[i].len;
	}

	/*
	 * Now munmap the old buffer and use the sorted buffer in its
	 * place:
	 */
	clear_snapshot_buffer(snapshot);
	snapshot->buf = snapshot->start = new_buffer;
	snapshot->eof = new_buffer + len;

cleanup:
	free(records);
}