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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
struct archiver_args {TYPE_1__* repo; int /*<<< orphan*/  baselen; struct commit* commit; scalar_t__ convert; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISREG (unsigned int) ; 
 int /*<<< orphan*/  convert_to_working_tree (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  format_subst (struct commit const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,void*,unsigned long,unsigned long) ; 
 void* strbuf_detach (struct strbuf*,size_t*) ; 

void *object_file_to_archive(const struct archiver_args *args,
			     const char *path, const struct object_id *oid,
			     unsigned int mode, enum object_type *type,
			     unsigned long *sizep)
{
	void *buffer;
	const struct commit *commit = args->convert ? args->commit : NULL;

	path += args->baselen;
	buffer = read_object_file(oid, type, sizep);
	if (buffer && S_ISREG(mode)) {
		struct strbuf buf = STRBUF_INIT;
		size_t size = 0;

		strbuf_attach(&buf, buffer, *sizep, *sizep + 1);
		convert_to_working_tree(args->repo->index, path, buf.buf, buf.len, &buf);
		if (commit)
			format_subst(commit, buf.buf, buf.len, &buf);
		buffer = strbuf_detach(&buf, &size);
		*sizep = size;
	}

	return buffer;
}