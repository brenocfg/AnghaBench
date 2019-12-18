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
typedef  int /*<<< orphan*/  uint32_t ;
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct pack_idx_option {int dummy; } ;
struct pack_idx_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ adjust_shared_perm (char const*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hash_to_hex (unsigned char*) ; 
 scalar_t__ rename (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* write_idx_file (int /*<<< orphan*/ *,struct pack_idx_entry**,int /*<<< orphan*/ ,struct pack_idx_option*,unsigned char*) ; 

void finish_tmp_packfile(struct strbuf *name_buffer,
			 const char *pack_tmp_name,
			 struct pack_idx_entry **written_list,
			 uint32_t nr_written,
			 struct pack_idx_option *pack_idx_opts,
			 unsigned char hash[])
{
	const char *idx_tmp_name;
	int basename_len = name_buffer->len;

	if (adjust_shared_perm(pack_tmp_name))
		die_errno("unable to make temporary pack file readable");

	idx_tmp_name = write_idx_file(NULL, written_list, nr_written,
				      pack_idx_opts, hash);
	if (adjust_shared_perm(idx_tmp_name))
		die_errno("unable to make temporary index file readable");

	strbuf_addf(name_buffer, "%s.pack", hash_to_hex(hash));

	if (rename(pack_tmp_name, name_buffer->buf))
		die_errno("unable to rename temporary pack file");

	strbuf_setlen(name_buffer, basename_len);

	strbuf_addf(name_buffer, "%s.idx", hash_to_hex(hash));
	if (rename(idx_tmp_name, name_buffer->buf))
		die_errno("unable to rename temporary index file");

	strbuf_setlen(name_buffer, basename_len);

	free((void *)idx_tmp_name);
}