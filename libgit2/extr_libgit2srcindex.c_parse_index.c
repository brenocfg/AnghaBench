#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct index_header {unsigned int entry_count; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_14__ {char* path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_16__ {int /*<<< orphan*/  length; } ;
struct TYPE_15__ {scalar_t__ dirty; TYPE_8__ entries; scalar_t__ ignore_case; int /*<<< orphan*/  checksum; int /*<<< orphan*/  version; scalar_t__ entries_map; } ;
typedef  TYPE_2__ git_index ;
typedef  int /*<<< orphan*/  git_idxmap_icase ;

/* Variables and functions */
 size_t INDEX_FOOTER_SIZE ; 
 size_t INDEX_HEADER_SIZE ; 
 int /*<<< orphan*/  INDEX_VERSION_NUMBER_COMP ; 
 int /*<<< orphan*/  INSERT_IN_MAP (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_hash_buf (int /*<<< orphan*/ *,char const*,size_t) ; 
 int git_idxmap_icase_resize (int /*<<< orphan*/ *,unsigned int) ; 
 int git_idxmap_resize (scalar_t__,unsigned int) ; 
 scalar_t__ git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromraw (int /*<<< orphan*/ *,unsigned char const*) ; 
 int git_vector_insert (TYPE_8__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_set_sorted (TYPE_8__*,int) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_8__*) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_1__*) ; 
 int index_error_invalid (char*) ; 
 int read_entry (TYPE_1__**,size_t*,TYPE_2__*,char const*,size_t,char const*) ; 
 int read_extension (size_t*,TYPE_2__*,char const*,size_t) ; 
 int read_header (struct index_header*,char const*) ; 

__attribute__((used)) static int parse_index(git_index *index, const char *buffer, size_t buffer_size)
{
	int error = 0;
	unsigned int i;
	struct index_header header = { 0 };
	git_oid checksum_calculated, checksum_expected;
	const char *last = NULL;
	const char *empty = "";

#define seek_forward(_increase) { \
	if (_increase >= buffer_size) { \
		error = index_error_invalid("ran out of data while parsing"); \
		goto done; } \
	buffer += _increase; \
	buffer_size -= _increase;\
}

	if (buffer_size < INDEX_HEADER_SIZE + INDEX_FOOTER_SIZE)
		return index_error_invalid("insufficient buffer space");

	/* Precalculate the SHA1 of the files's contents -- we'll match it to
	 * the provided SHA1 in the footer */
	git_hash_buf(&checksum_calculated, buffer, buffer_size - INDEX_FOOTER_SIZE);

	/* Parse header */
	if ((error = read_header(&header, buffer)) < 0)
		return error;

	index->version = header.version;
	if (index->version >= INDEX_VERSION_NUMBER_COMP)
		last = empty;

	seek_forward(INDEX_HEADER_SIZE);

	assert(!index->entries.length);

	if (index->ignore_case &&
	    (error = git_idxmap_icase_resize((git_idxmap_icase *) index->entries_map,
					     header.entry_count)) < 0)
		return error;
	else if ((error = git_idxmap_resize(index->entries_map, header.entry_count)) < 0)
		return error;

	/* Parse all the entries */
	for (i = 0; i < header.entry_count && buffer_size > INDEX_FOOTER_SIZE; ++i) {
		git_index_entry *entry = NULL;
		size_t entry_size;

		if ((error = read_entry(&entry, &entry_size, index, buffer, buffer_size, last)) < 0) {
			error = index_error_invalid("invalid entry");
			goto done;
		}

		if ((error = git_vector_insert(&index->entries, entry)) < 0) {
			index_entry_free(entry);
			goto done;
		}

		INSERT_IN_MAP(index, entry, error);

		if (error < 0) {
			index_entry_free(entry);
			goto done;
		}
		error = 0;

		if (index->version >= INDEX_VERSION_NUMBER_COMP)
			last = entry->path;

		seek_forward(entry_size);
	}

	if (i != header.entry_count) {
		error = index_error_invalid("header entries changed while parsing");
		goto done;
	}

	/* There's still space for some extensions! */
	while (buffer_size > INDEX_FOOTER_SIZE) {
		size_t extension_size;

		if ((error = read_extension(&extension_size, index, buffer, buffer_size)) < 0) {
			goto done;
		}

		seek_forward(extension_size);
	}

	if (buffer_size != INDEX_FOOTER_SIZE) {
		error = index_error_invalid(
			"buffer size does not match index footer size");
		goto done;
	}

	/* 160-bit SHA-1 over the content of the index file before this checksum. */
	git_oid_fromraw(&checksum_expected, (const unsigned char *)buffer);

	if (git_oid__cmp(&checksum_calculated, &checksum_expected) != 0) {
		error = index_error_invalid(
			"calculated checksum does not match expected");
		goto done;
	}

	git_oid_cpy(&index->checksum, &checksum_calculated);

#undef seek_forward

	/* Entries are stored case-sensitively on disk, so re-sort now if
	 * in-memory index is supposed to be case-insensitive
	 */
	git_vector_set_sorted(&index->entries, !index->ignore_case);
	git_vector_sort(&index->entries);

	index->dirty = 0;
done:
	return error;
}