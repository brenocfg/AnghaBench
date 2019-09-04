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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct process_trailer_options {scalar_t__ in_place; int /*<<< orphan*/  only_trailers; int /*<<< orphan*/  only_input; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arg_head ; 
 int /*<<< orphan*/ * create_in_place_tempfile (char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ensure_configured () ; 
 int /*<<< orphan*/  free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (scalar_t__,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  print_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct process_trailer_options const*) ; 
 int /*<<< orphan*/  process_command_line_args (int /*<<< orphan*/ *,struct list_head*) ; 
 size_t process_input_file (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,struct process_trailer_options const*) ; 
 int /*<<< orphan*/  process_trailers_lists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_input_file (struct strbuf*,char const*) ; 
 scalar_t__ rename_tempfile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  trailers_tempfile ; 

void process_trailers(const char *file,
		      const struct process_trailer_options *opts,
		      struct list_head *new_trailer_head)
{
	LIST_HEAD(head);
	struct strbuf sb = STRBUF_INIT;
	size_t trailer_end;
	FILE *outfile = stdout;

	ensure_configured();

	read_input_file(&sb, file);

	if (opts->in_place)
		outfile = create_in_place_tempfile(file);

	/* Print the lines before the trailers */
	trailer_end = process_input_file(outfile, sb.buf, &head, opts);

	if (!opts->only_input) {
		LIST_HEAD(arg_head);
		process_command_line_args(&arg_head, new_trailer_head);
		process_trailers_lists(&head, &arg_head);
	}

	print_all(outfile, &head, opts);

	free_all(&head);

	/* Print the lines after the trailers as is */
	if (!opts->only_trailers)
		fwrite(sb.buf + trailer_end, 1, sb.len - trailer_end, outfile);

	if (opts->in_place)
		if (rename_tempfile(&trailers_tempfile, file))
			die_errno(_("could not rename temporary file to %s"), file);

	strbuf_release(&sb);
}