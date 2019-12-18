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
struct sparse {scalar_t__ size; scalar_t__ type; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ DATA ; 
 scalar_t__ END ; 
 scalar_t__ HOLE ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 scalar_t__ archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  archive_read_disk_open (struct archive*,char const*) ; 
 int /*<<< orphan*/  archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMemoryFilledWith (char const*,int,char) ; 
 int /*<<< orphan*/  create_sparse_file (char const*,struct sparse const*) ; 
 int /*<<< orphan*/  failure (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
verify_sparse_file(struct archive *a, const char *path,
    const struct sparse *sparse, int expected_holes)
{
	struct archive_entry *ae;
	const void *buff;
	size_t bytes_read;
	int64_t offset, expected_offset, last_offset;
	int holes_seen = 0;

	create_sparse_file(path, sparse);
	assert((ae = archive_entry_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, path));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));

	expected_offset = 0;
	last_offset = 0;
	while (ARCHIVE_OK == archive_read_data_block(a, &buff, &bytes_read,
	    &offset)) {
		const char *start = buff;
#if DEBUG
		fprintf(stderr, "%s: bytes_read=%d offset=%d\n", path, (int)bytes_read, (int)offset);
#endif
		if (offset > last_offset) {
			++holes_seen;
		}
		/* Blocks entirely before the data we just read. */
		while (expected_offset + (int64_t)sparse->size < offset) {
#if DEBUG
			fprintf(stderr, "    skipping expected_offset=%d, size=%d\n", (int)expected_offset, (int)sparse->size);
#endif
			/* Must be holes. */
			assert(sparse->type == HOLE);
			expected_offset += sparse->size;
			++sparse;
		}
		/* Block that overlaps beginning of data */
		if (expected_offset < offset
		    && expected_offset + (int64_t)sparse->size <= offset + (int64_t)bytes_read) {
			const char *end = (const char *)buff + (expected_offset - offset) + (size_t)sparse->size;
#if DEBUG
			fprintf(stderr, "    overlapping hole expected_offset=%d, size=%d\n", (int)expected_offset, (int)sparse->size);
#endif
			/* Must be a hole, overlap must be filled with '\0' */
			if (assert(sparse->type == HOLE)) {
				assertMemoryFilledWith(start, end - start, '\0');
			}
			start = end;
			expected_offset += sparse->size;
			++sparse;
		}
		/* Blocks completely contained in data we just read. */
		while (expected_offset + (int64_t)sparse->size <= offset + (int64_t)bytes_read) {
			const char *end = (const char *)buff + (expected_offset - offset) + (size_t)sparse->size;
			if (sparse->type == HOLE) {
#if DEBUG
				fprintf(stderr, "    contained hole expected_offset=%d, size=%d\n", (int)expected_offset, (int)sparse->size);
#endif

				/* verify data corresponding to hole is '\0' */
				if (end > (const char *)buff + bytes_read) {
					end = (const char *)buff + bytes_read;
				}
				assertMemoryFilledWith(start, end - start, '\0');
				start = end;
				expected_offset += sparse->size;
				++sparse;
			} else if (sparse->type == DATA) {
#if DEBUG
				fprintf(stderr, "    contained data expected_offset=%d, size=%d\n", (int)expected_offset, (int)sparse->size);
#endif
				/* verify data corresponding to hole is ' ' */
				if (assert(expected_offset + sparse->size <= offset + bytes_read)) {
					assert(start == (const char *)buff + (size_t)(expected_offset - offset));
					assertMemoryFilledWith(start, end - start, ' ');
				}
				start = end;
				expected_offset += sparse->size;
				++sparse;
			} else {
				break;
			}
		}
		/* Block that overlaps end of data */
		if (expected_offset < offset + (int64_t)bytes_read) {
			const char *end = (const char *)buff + bytes_read;
#if DEBUG
			fprintf(stderr, "    trailing overlap expected_offset=%d, size=%d\n", (int)expected_offset, (int)sparse->size);
#endif
			/* Must be a hole, overlap must be filled with '\0' */
			if (assert(sparse->type == HOLE)) {
				assertMemoryFilledWith(start, end - start, '\0');
			}
		}
		last_offset = offset + bytes_read;
	}
	/* Count a hole at EOF? */
	if (last_offset < archive_entry_size(ae)) {
		++holes_seen;
	}

	/* Verify blocks after last read */
	while (sparse->type == HOLE) {
		expected_offset += sparse->size;
		++sparse;
	}
	assert(sparse->type == END);
	assertEqualInt(expected_offset, archive_entry_size(ae));

	failure(path);
	assertEqualInt(holes_seen, expected_holes);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	archive_entry_free(ae);
}