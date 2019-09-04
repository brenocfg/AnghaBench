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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct ref_store {int dummy; } ;
struct files_ref_store {int dummy; } ;
typedef  int /*<<< orphan*/  each_reflog_ent_fn ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  REF_STORE_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  errno ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 char* find_beginning_of_line (char*,char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int show_one_reflog_ent (struct strbuf*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int files_for_each_reflog_ent_reverse(struct ref_store *ref_store,
					     const char *refname,
					     each_reflog_ent_fn fn,
					     void *cb_data)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ,
			       "for_each_reflog_ent_reverse");
	struct strbuf sb = STRBUF_INIT;
	FILE *logfp;
	long pos;
	int ret = 0, at_tail = 1;

	files_reflog_path(refs, &sb, refname);
	logfp = fopen(sb.buf, "r");
	strbuf_release(&sb);
	if (!logfp)
		return -1;

	/* Jump to the end */
	if (fseek(logfp, 0, SEEK_END) < 0)
		ret = error("cannot seek back reflog for %s: %s",
			    refname, strerror(errno));
	pos = ftell(logfp);
	while (!ret && 0 < pos) {
		int cnt;
		size_t nread;
		char buf[BUFSIZ];
		char *endp, *scanp;

		/* Fill next block from the end */
		cnt = (sizeof(buf) < pos) ? sizeof(buf) : pos;
		if (fseek(logfp, pos - cnt, SEEK_SET)) {
			ret = error("cannot seek back reflog for %s: %s",
				    refname, strerror(errno));
			break;
		}
		nread = fread(buf, cnt, 1, logfp);
		if (nread != 1) {
			ret = error("cannot read %d bytes from reflog for %s: %s",
				    cnt, refname, strerror(errno));
			break;
		}
		pos -= cnt;

		scanp = endp = buf + cnt;
		if (at_tail && scanp[-1] == '\n')
			/* Looking at the final LF at the end of the file */
			scanp--;
		at_tail = 0;

		while (buf < scanp) {
			/*
			 * terminating LF of the previous line, or the beginning
			 * of the buffer.
			 */
			char *bp;

			bp = find_beginning_of_line(buf, scanp);

			if (*bp == '\n') {
				/*
				 * The newline is the end of the previous line,
				 * so we know we have complete line starting
				 * at (bp + 1). Prefix it onto any prior data
				 * we collected for the line and process it.
				 */
				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
				scanp = bp;
				endp = bp + 1;
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				if (ret)
					break;
			} else if (!pos) {
				/*
				 * We are at the start of the buffer, and the
				 * start of the file; there is no previous
				 * line, and we have everything for this one.
				 * Process it, and we can end the loop.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				break;
			}

			if (bp == buf) {
				/*
				 * We are at the start of the buffer, and there
				 * is more file to read backwards. Which means
				 * we are in the middle of a line. Note that we
				 * may get here even if *bp was a newline; that
				 * just means we are at the exact end of the
				 * previous line, rather than some spot in the
				 * middle.
				 *
				 * Save away what we have to be combined with
				 * the data from the next read.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				break;
			}
		}

	}
	if (!ret && sb.len)
		BUG("reverse reflog parser had leftover data");

	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}