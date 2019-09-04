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
struct index_entry {int dummy; } ;
struct git_delta_index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/  git__is_ulong (size_t) ; 
 void* git__malloc (size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int lookup_index_alloc(
	void **out, unsigned long *out_len, size_t entries, size_t hash_count)
{
	size_t entries_len, hash_len, index_len;

	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&entries_len, entries, sizeof(struct index_entry));
	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&hash_len, hash_count, sizeof(struct index_entry *));

	GIT_ERROR_CHECK_ALLOC_ADD(&index_len, sizeof(struct git_delta_index), entries_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&index_len, index_len, hash_len);

	if (!git__is_ulong(index_len)) {
		git_error_set(GIT_ERROR_NOMEMORY, "overly large delta");
		return -1;
	}

	*out = git__malloc(index_len);
	GIT_ERROR_CHECK_ALLOC(*out);

	*out_len = (unsigned long)index_len;
	return 0;
}