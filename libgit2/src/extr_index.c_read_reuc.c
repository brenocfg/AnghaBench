#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * oid; scalar_t__* mode; } ;
typedef  TYPE_1__ git_index_reuc_entry ;
struct TYPE_13__ {scalar_t__ _alloc_size; } ;
struct TYPE_12__ {TYPE_6__ reuc; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ git__strntol64 (scalar_t__*,char const*,size_t,char const**,int) ; 
 int /*<<< orphan*/  git_oid_fromraw (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ git_vector_init (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ git_vector_insert (TYPE_6__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_set_sorted (TYPE_6__*,int) ; 
 int /*<<< orphan*/  index_entry_reuc_free (TYPE_1__*) ; 
 int index_error_invalid (char*) ; 
 int p_strnlen (char const*,size_t) ; 
 int /*<<< orphan*/  reuc_cmp ; 
 TYPE_1__* reuc_entry_alloc (char const*) ; 

__attribute__((used)) static int read_reuc(git_index *index, const char *buffer, size_t size)
{
	const char *endptr;
	size_t len;
	int i;

	/* If called multiple times, the vector might already be initialized */
	if (index->reuc._alloc_size == 0 &&
		git_vector_init(&index->reuc, 16, reuc_cmp) < 0)
		return -1;

	while (size) {
		git_index_reuc_entry *lost;

		len = p_strnlen(buffer, size) + 1;
		if (size <= len)
			return index_error_invalid("reading reuc entries");

		lost = reuc_entry_alloc(buffer);
		GIT_ERROR_CHECK_ALLOC(lost);

		size -= len;
		buffer += len;

		/* read 3 ASCII octal numbers for stage entries */
		for (i = 0; i < 3; i++) {
			int64_t tmp;

			if (git__strntol64(&tmp, buffer, size, &endptr, 8) < 0 ||
				!endptr || endptr == buffer || *endptr ||
				tmp < 0 || tmp > UINT32_MAX) {
				index_entry_reuc_free(lost);
				return index_error_invalid("reading reuc entry stage");
			}

			lost->mode[i] = (uint32_t)tmp;

			len = (endptr + 1) - buffer;
			if (size <= len) {
				index_entry_reuc_free(lost);
				return index_error_invalid("reading reuc entry stage");
			}

			size -= len;
			buffer += len;
		}

		/* read up to 3 OIDs for stage entries */
		for (i = 0; i < 3; i++) {
			if (!lost->mode[i])
				continue;
			if (size < 20) {
				index_entry_reuc_free(lost);
				return index_error_invalid("reading reuc entry oid");
			}

			git_oid_fromraw(&lost->oid[i], (const unsigned char *) buffer);
			size -= 20;
			buffer += 20;
		}

		/* entry was read successfully - insert into reuc vector */
		if (git_vector_insert(&index->reuc, lost) < 0)
			return -1;
	}

	/* entries are guaranteed to be sorted on-disk */
	git_vector_set_sorted(&index->reuc, true);

	return 0;
}