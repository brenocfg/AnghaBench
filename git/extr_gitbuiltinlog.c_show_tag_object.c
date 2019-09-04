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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
struct rev_info {TYPE_1__ diffopt; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_TAG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  show_tagger (char const*,struct rev_info*) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 

__attribute__((used)) static int show_tag_object(const struct object_id *oid, struct rev_info *rev)
{
	unsigned long size;
	enum object_type type;
	char *buf = read_object_file(oid, &type, &size);
	int offset = 0;

	if (!buf)
		return error(_("could not read object %s"), oid_to_hex(oid));

	assert(type == OBJ_TAG);
	while (offset < size && buf[offset] != '\n') {
		int new_offset = offset + 1;
		const char *ident;
		while (new_offset < size && buf[new_offset++] != '\n')
			; /* do nothing */
		if (skip_prefix(buf + offset, "tagger ", &ident))
			show_tagger(ident, rev);
		offset = new_offset;
	}

	if (offset < size)
		fwrite(buf + offset, size - offset, 1, rev->diffopt.file);
	free(buf);
	return 0;
}