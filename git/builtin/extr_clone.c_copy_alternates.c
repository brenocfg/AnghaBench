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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_to_alternates_file (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_absolute_path (char*) ; 
 char* mkpathdup (char*,char const*,char*) ; 
 int /*<<< orphan*/  normalize_path_copy (char*,char*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char*) ; 
 int /*<<< orphan*/ * xfopen (char*,char*) ; 

__attribute__((used)) static void copy_alternates(struct strbuf *src, const char *src_repo)
{
	/*
	 * Read from the source objects/info/alternates file
	 * and copy the entries to corresponding file in the
	 * destination repository with add_to_alternates_file().
	 * Both src and dst have "$path/objects/info/alternates".
	 *
	 * Instead of copying bit-for-bit from the original,
	 * we need to append to existing one so that the already
	 * created entry via "clone -s" is not lost, and also
	 * to turn entries with paths relative to the original
	 * absolute, so that they can be used in the new repository.
	 */
	FILE *in = xfopen(src->buf, "r");
	struct strbuf line = STRBUF_INIT;

	while (strbuf_getline(&line, in) != EOF) {
		char *abs_path;
		if (!line.len || line.buf[0] == '#')
			continue;
		if (is_absolute_path(line.buf)) {
			add_to_alternates_file(line.buf);
			continue;
		}
		abs_path = mkpathdup("%s/objects/%s", src_repo, line.buf);
		if (!normalize_path_copy(abs_path, abs_path))
			add_to_alternates_file(abs_path);
		else
			warning("skipping invalid relative alternate: %s/%s",
				src_repo, line.buf);
		free(abs_path);
	}
	strbuf_release(&line);
	fclose(in);
}