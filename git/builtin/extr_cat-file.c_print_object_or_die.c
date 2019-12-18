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
struct object_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ sizep; int /*<<< orphan*/  typep; } ;
struct expand_data {scalar_t__ type; unsigned long size; TYPE_1__ info; int /*<<< orphan*/  rest; struct object_id oid; } ;
struct batch_options {char cmdmode; scalar_t__ buffer_output; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char) ; 
 scalar_t__ OBJ_BLOB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batch_write (struct batch_options*,void*,unsigned long) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ filter_object (int /*<<< orphan*/ ,int,struct object_id const*,char**,unsigned long*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stream_blob (struct object_id const*) ; 
 int /*<<< orphan*/  textconv_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct object_id const*,int,char**,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void print_object_or_die(struct batch_options *opt, struct expand_data *data)
{
	const struct object_id *oid = &data->oid;

	assert(data->info.typep);

	if (data->type == OBJ_BLOB) {
		if (opt->buffer_output)
			fflush(stdout);
		if (opt->cmdmode) {
			char *contents;
			unsigned long size;

			if (!data->rest)
				die("missing path for '%s'", oid_to_hex(oid));

			if (opt->cmdmode == 'w') {
				if (filter_object(data->rest, 0100644, oid,
						  &contents, &size))
					die("could not convert '%s' %s",
					    oid_to_hex(oid), data->rest);
			} else if (opt->cmdmode == 'c') {
				enum object_type type;
				if (!textconv_object(the_repository,
						     data->rest, 0100644, oid,
						     1, &contents, &size))
					contents = read_object_file(oid,
								    &type,
								    &size);
				if (!contents)
					die("could not convert '%s' %s",
					    oid_to_hex(oid), data->rest);
			} else
				BUG("invalid cmdmode: %c", opt->cmdmode);
			batch_write(opt, contents, size);
			free(contents);
		} else {
			stream_blob(oid);
		}
	}
	else {
		enum object_type type;
		unsigned long size;
		void *contents;

		contents = read_object_file(oid, &type, &size);
		if (!contents)
			die("object %s disappeared", oid_to_hex(oid));
		if (type != data->type)
			die("object %s changed type!?", oid_to_hex(oid));
		if (data->info.sizep && size != data->size)
			die("object %s changed size!?", oid_to_hex(oid));

		batch_write(opt, contents, size);
		free(contents);
	}
}