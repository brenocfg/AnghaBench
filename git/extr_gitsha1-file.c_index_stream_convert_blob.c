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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
 int /*<<< orphan*/  OBJ_BLOB ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  convert_to_git_filter_fd (struct index_state*,char const*,int,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_conv_flags (unsigned int) ; 
 int hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ) ; 
 char const* would_convert_to_git_filter_fd (struct index_state*,char const*) ; 
 int write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int index_stream_convert_blob(struct index_state *istate,
				     struct object_id *oid,
				     int fd,
				     const char *path,
				     unsigned flags)
{
	int ret;
	const int write_object = flags & HASH_WRITE_OBJECT;
	struct strbuf sbuf = STRBUF_INIT;

	assert(path);
	assert(would_convert_to_git_filter_fd(istate, path));

	convert_to_git_filter_fd(istate, path, fd, &sbuf,
				 get_conv_flags(flags));

	if (write_object)
		ret = write_object_file(sbuf.buf, sbuf.len, type_name(OBJ_BLOB),
					oid);
	else
		ret = hash_object_file(sbuf.buf, sbuf.len, type_name(OBJ_BLOB),
				       oid);
	strbuf_release(&sbuf);
	return ret;
}