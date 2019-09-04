#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct index_extension {int extension_size; char* signature; } ;
struct TYPE_5__ {int /*<<< orphan*/  tree_pool; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  INDEX_EXT_CONFLICT_NAME_SIG ; 
 int /*<<< orphan*/  INDEX_EXT_TREECACHE_SIG ; 
 int /*<<< orphan*/  INDEX_EXT_UNMERGED_SIG ; 
 size_t INDEX_FOOTER_SIZE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ git_tree_cache_read (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_error_invalid (char*) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct index_extension*,char const*,int) ; 
 int ntohl (int) ; 
 scalar_t__ read_conflict_names (TYPE_1__*,char const*,size_t) ; 
 scalar_t__ read_reuc (TYPE_1__*,char const*,size_t) ; 

__attribute__((used)) static int read_extension(size_t *read_len, git_index *index, const char *buffer, size_t buffer_size)
{
	struct index_extension dest;
	size_t total_size;

	/* buffer is not guaranteed to be aligned */
	memcpy(&dest, buffer, sizeof(struct index_extension));
	dest.extension_size = ntohl(dest.extension_size);

	total_size = dest.extension_size + sizeof(struct index_extension);

	if (dest.extension_size > total_size ||
		buffer_size < total_size ||
		buffer_size - total_size < INDEX_FOOTER_SIZE) {
		index_error_invalid("extension is truncated");
		return -1;
	}

	/* optional extension */
	if (dest.signature[0] >= 'A' && dest.signature[0] <= 'Z') {
		/* tree cache */
		if (memcmp(dest.signature, INDEX_EXT_TREECACHE_SIG, 4) == 0) {
			if (git_tree_cache_read(&index->tree, buffer + 8, dest.extension_size, &index->tree_pool) < 0)
				return -1;
		} else if (memcmp(dest.signature, INDEX_EXT_UNMERGED_SIG, 4) == 0) {
			if (read_reuc(index, buffer + 8, dest.extension_size) < 0)
				return -1;
		} else if (memcmp(dest.signature, INDEX_EXT_CONFLICT_NAME_SIG, 4) == 0) {
			if (read_conflict_names(index, buffer + 8, dest.extension_size) < 0)
				return -1;
		}
		/* else, unsupported extension. We cannot parse this, but we can skip
		 * it by returning `total_size */
	} else {
		/* we cannot handle non-ignorable extensions;
		 * in fact they aren't even defined in the standard */
		git_error_set(GIT_ERROR_INDEX, "unsupported mandatory extension: '%.4s'", dest.signature);
		return -1;
	}

	*read_len = total_size;

	return 0;
}