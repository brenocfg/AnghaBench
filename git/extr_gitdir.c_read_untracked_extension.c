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
struct untracked_cache {int /*<<< orphan*/  root; int /*<<< orphan*/  exclude_per_dir; int /*<<< orphan*/  dir_flags; int /*<<< orphan*/  ss_excludes_file; int /*<<< orphan*/  ss_info_exclude; int /*<<< orphan*/  ident; } ;
struct read_data {unsigned char const* data; unsigned char const* end; int index; void* sha1_valid; void* check_only; void* valid; int /*<<< orphan*/  ucd; } ;
struct ondisk_untracked_cache {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int /*<<< orphan*/ ,int) ; 
 int decode_varint (unsigned char const**) ; 
 int /*<<< orphan*/  dir_flags ; 
 int /*<<< orphan*/  ewah_each_bit (void*,int /*<<< orphan*/ ,struct read_data*) ; 
 int /*<<< orphan*/  ewah_free (void*) ; 
 void* ewah_new () ; 
 int ewah_read_mmap (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  excludes_file_stat ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_untracked_cache (struct untracked_cache*) ; 
 int /*<<< orphan*/  get_be32 (unsigned char const*) ; 
 int /*<<< orphan*/  info_exclude_stat ; 
 int /*<<< orphan*/  load_oid_stat (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*) ; 
 int ouc_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_oid ; 
 scalar_t__ read_one_dir (int /*<<< orphan*/ *,struct read_data*) ; 
 int /*<<< orphan*/  read_stat ; 
 int /*<<< orphan*/  set_check_only ; 
 int /*<<< orphan*/  strbuf_add (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_1__* the_hash_algo ; 
 struct untracked_cache* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct untracked_cache *read_untracked_extension(const void *data, unsigned long sz)
{
	struct untracked_cache *uc;
	struct read_data rd;
	const unsigned char *next = data, *end = (const unsigned char *)data + sz;
	const char *ident;
	int ident_len;
	ssize_t len;
	const char *exclude_per_dir;
	const unsigned hashsz = the_hash_algo->rawsz;
	const unsigned offset = sizeof(struct ondisk_untracked_cache);
	const unsigned exclude_per_dir_offset = offset + 2 * hashsz;

	if (sz <= 1 || end[-1] != '\0')
		return NULL;
	end--;

	ident_len = decode_varint(&next);
	if (next + ident_len > end)
		return NULL;
	ident = (const char *)next;
	next += ident_len;

	if (next + exclude_per_dir_offset + 1 > end)
		return NULL;

	uc = xcalloc(1, sizeof(*uc));
	strbuf_init(&uc->ident, ident_len);
	strbuf_add(&uc->ident, ident, ident_len);
	load_oid_stat(&uc->ss_info_exclude,
		      next + ouc_offset(info_exclude_stat),
		      next + offset);
	load_oid_stat(&uc->ss_excludes_file,
		      next + ouc_offset(excludes_file_stat),
		      next + offset + hashsz);
	uc->dir_flags = get_be32(next + ouc_offset(dir_flags));
	exclude_per_dir = (const char *)next + exclude_per_dir_offset;
	uc->exclude_per_dir = xstrdup(exclude_per_dir);
	/* NUL after exclude_per_dir is covered by sizeof(*ouc) */
	next += exclude_per_dir_offset + strlen(exclude_per_dir) + 1;
	if (next >= end)
		goto done2;

	len = decode_varint(&next);
	if (next > end || len == 0)
		goto done2;

	rd.valid      = ewah_new();
	rd.check_only = ewah_new();
	rd.sha1_valid = ewah_new();
	rd.data	      = next;
	rd.end	      = end;
	rd.index      = 0;
	ALLOC_ARRAY(rd.ucd, len);

	if (read_one_dir(&uc->root, &rd) || rd.index != len)
		goto done;

	next = rd.data;
	len = ewah_read_mmap(rd.valid, next, end - next);
	if (len < 0)
		goto done;

	next += len;
	len = ewah_read_mmap(rd.check_only, next, end - next);
	if (len < 0)
		goto done;

	next += len;
	len = ewah_read_mmap(rd.sha1_valid, next, end - next);
	if (len < 0)
		goto done;

	ewah_each_bit(rd.check_only, set_check_only, &rd);
	rd.data = next + len;
	ewah_each_bit(rd.valid, read_stat, &rd);
	ewah_each_bit(rd.sha1_valid, read_oid, &rd);
	next = rd.data;

done:
	free(rd.ucd);
	ewah_free(rd.valid);
	ewah_free(rd.check_only);
	ewah_free(rd.sha1_valid);
done2:
	if (next != end) {
		free_untracked_cache(uc);
		uc = NULL;
	}
	return uc;
}