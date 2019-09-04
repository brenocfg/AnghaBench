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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 
 scalar_t__ parse_pack_def (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int read_pack_info_file(const char *infofile)
{
	FILE *fp;
	struct strbuf line = STRBUF_INIT;
	int old_cnt = 0;
	int stale = 1;

	fp = fopen_or_warn(infofile, "r");
	if (!fp)
		return 1; /* nonexistent is not an error. */

	while (strbuf_getline(&line, fp) != EOF) {
		const char *arg;

		if (!line.len)
			continue;

		if (skip_prefix(line.buf, "P ", &arg)) {
			/* P name */
			if (parse_pack_def(arg, old_cnt++))
				goto out_stale;
		} else if (line.buf[0] == 'D') {
			/* we used to emit D but that was misguided. */
			goto out_stale;
		} else if (line.buf[0] == 'T') {
			/* we used to emit T but nobody uses it. */
			goto out_stale;
		} else {
			error("unrecognized: %s", line.buf);
		}
	}
	stale = 0;

 out_stale:
	strbuf_release(&line);
	fclose(fp);
	return stale;
}