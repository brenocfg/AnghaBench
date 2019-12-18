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
struct string_list {int dummy; } ;
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct pack_objects_args {int dummy; } ;
struct child_process {int in; int /*<<< orphan*/  out; } ;
struct TYPE_2__ {scalar_t__ hexsz; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FOR_EACH_OBJECT_PROMISOR_ONLY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,struct child_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mkpathdup (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  packtmp ; 
 int /*<<< orphan*/  prepare_pack_objects (struct child_process*,struct pack_objects_args const*) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  write_oid ; 
 int /*<<< orphan*/ * xfdopen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void repack_promisor_objects(const struct pack_objects_args *args,
				    struct string_list *names)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	FILE *out;
	struct strbuf line = STRBUF_INIT;

	prepare_pack_objects(&cmd, args);
	cmd.in = -1;

	/*
	 * NEEDSWORK: Giving pack-objects only the OIDs without any ordering
	 * hints may result in suboptimal deltas in the resulting pack. See if
	 * the OIDs can be sent with fake paths such that pack-objects can use a
	 * {type -> existing pack order} ordering when computing deltas instead
	 * of a {type -> size} ordering, which may produce better deltas.
	 */
	for_each_packed_object(write_oid, &cmd,
			       FOR_EACH_OBJECT_PROMISOR_ONLY);

	if (cmd.in == -1)
		/* No packed objects; cmd was never started */
		return;

	close(cmd.in);

	out = xfdopen(cmd.out, "r");
	while (strbuf_getline_lf(&line, out) != EOF) {
		char *promisor_name;
		int fd;
		if (line.len != the_hash_algo->hexsz)
			die(_("repack: Expecting full hex object ID lines only from pack-objects."));
		string_list_append(names, line.buf);

		/*
		 * pack-objects creates the .pack and .idx files, but not the
		 * .promisor file. Create the .promisor file, which is empty.
		 *
		 * NEEDSWORK: fetch-pack sometimes generates non-empty
		 * .promisor files containing the ref names and associated
		 * hashes at the point of generation of the corresponding
		 * packfile, but this would not preserve their contents. Maybe
		 * concatenate the contents of all .promisor files instead of
		 * just creating a new empty file.
		 */
		promisor_name = mkpathdup("%s-%s.promisor", packtmp,
					  line.buf);
		fd = open(promisor_name, O_CREAT|O_EXCL|O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("unable to create '%s'"), promisor_name);
		close(fd);
		free(promisor_name);
	}
	fclose(out);
	if (finish_command(&cmd))
		die(_("could not finish pack-objects to repack promisor objects"));
}