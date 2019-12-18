#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mparse {int line; int filenc; int options; struct buf* secondary; struct buf* loop; TYPE_2__* man; int /*<<< orphan*/  roff; scalar_t__ reparse_count; } ;
struct buf {int sz; char* buf; struct buf* next; } ;
struct TYPE_4__ {void* sodest; int /*<<< orphan*/  macroset; } ;
struct TYPE_5__ {TYPE_1__ meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACROSET_MDOC ; 
 int /*<<< orphan*/  MACROSET_NONE ; 
 int /*<<< orphan*/  MANDOCERR_CHAR_BAD ; 
 int /*<<< orphan*/  MANDOCERR_CHAR_UNSUPP ; 
 int /*<<< orphan*/  MANDOCERR_ROFFLOOP ; 
 int /*<<< orphan*/  MANDOCERR_SO_FAIL ; 
 int /*<<< orphan*/  MANDOCERR_WHILE_FAIL ; 
 int /*<<< orphan*/  MANDOCERR_WHILE_INTO ; 
 int /*<<< orphan*/  MANDOCERR_WHILE_NEST ; 
 int /*<<< orphan*/  MANDOCERR_WHILE_OUTOF ; 
 int MPARSE_LATIN1 ; 
 int MPARSE_SO ; 
 int MPARSE_UTF8 ; 
 scalar_t__ REPARSE_LIMIT ; 
 int ROFF_APPEND ; 
#define  ROFF_CONT 135 
#define  ROFF_IGN 134 
#define  ROFF_LOOPCONT 133 
#define  ROFF_LOOPEXIT 132 
 int ROFF_LOOPMASK ; 
 int ROFF_MASK ; 
#define  ROFF_REPARSE 131 
#define  ROFF_RERUN 130 
#define  ROFF_SO 129 
 int ROFF_USERCALL ; 
 int ROFF_USERRET ; 
#define  ROFF_WHILE 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  choose_parser (struct mparse*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_buf_list (struct buf*) ; 
 int man_parseln (TYPE_2__*,int,char*,int) ; 
 size_t mandoc_asprintf (char**,char*,char*) ; 
 void* mandoc_malloc (int) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,size_t,char*,...) ; 
 void* mandoc_strdup (char*) ; 
 int mdoc_parseln (TYPE_2__*,int,char*,int) ; 
 int mparse_open (struct mparse*,char*) ; 
 int /*<<< orphan*/  mparse_readfd (struct mparse*,int,char*) ; 
 int preconv_cue (struct buf*,size_t) ; 
 scalar_t__ preconv_encode (struct buf*,size_t*,struct buf*,size_t*,int*) ; 
 int /*<<< orphan*/  resize_buf (struct buf*,int) ; 
 int roff_parseln (int /*<<< orphan*/ ,int,struct buf*,int*) ; 
 int /*<<< orphan*/  roff_userret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 void* strlen (char*) ; 

__attribute__((used)) static int
mparse_buf_r(struct mparse *curp, struct buf blk, size_t i, int start)
{
	struct buf	 ln;
	struct buf	*firstln, *lastln, *thisln, *loop;
	char		*cp;
	size_t		 pos; /* byte number in the ln buffer */
	int		 line_result, result;
	int		 of;
	int		 lnn; /* line number in the real file */
	int		 fd;
	int		 inloop; /* Saw .while on this level. */
	unsigned char	 c;

	ln.sz = 256;
	ln.buf = mandoc_malloc(ln.sz);
	ln.next = NULL;
	firstln = lastln = loop = NULL;
	lnn = curp->line;
	pos = 0;
	inloop = 0;
	result = ROFF_CONT;

	while (i < blk.sz && (blk.buf[i] != '\0' || pos != 0)) {
		if (start) {
			curp->line = lnn;
			curp->reparse_count = 0;

			if (lnn < 3 &&
			    curp->filenc & MPARSE_UTF8 &&
			    curp->filenc & MPARSE_LATIN1)
				curp->filenc = preconv_cue(&blk, i);
		}

		while (i < blk.sz && (start || blk.buf[i] != '\0')) {

			/*
			 * When finding an unescaped newline character,
			 * leave the character loop to process the line.
			 * Skip a preceding carriage return, if any.
			 */

			if ('\r' == blk.buf[i] && i + 1 < blk.sz &&
			    '\n' == blk.buf[i + 1])
				++i;
			if ('\n' == blk.buf[i]) {
				++i;
				++lnn;
				break;
			}

			/*
			 * Make sure we have space for the worst
			 * case of 12 bytes: "\\[u10ffff]\n\0"
			 */

			if (pos + 12 > ln.sz)
				resize_buf(&ln, 256);

			/*
			 * Encode 8-bit input.
			 */

			c = blk.buf[i];
			if (c & 0x80) {
				if ( ! (curp->filenc && preconv_encode(
				    &blk, &i, &ln, &pos, &curp->filenc))) {
					mandoc_msg(MANDOCERR_CHAR_BAD,
					    curp->line, pos, "0x%x", c);
					ln.buf[pos++] = '?';
					i++;
				}
				continue;
			}

			/*
			 * Exclude control characters.
			 */

			if (c == 0x7f || (c < 0x20 && c != 0x09)) {
				mandoc_msg(c == 0x00 || c == 0x04 ||
				    c > 0x0a ? MANDOCERR_CHAR_BAD :
				    MANDOCERR_CHAR_UNSUPP,
				    curp->line, pos, "0x%x", c);
				i++;
				if (c != '\r')
					ln.buf[pos++] = '?';
				continue;
			}

			ln.buf[pos++] = blk.buf[i++];
		}
		ln.buf[pos] = '\0';

		/*
		 * Maintain a lookaside buffer of all lines.
		 * parsed from this input source.
		 */

		thisln = mandoc_malloc(sizeof(*thisln));
		thisln->buf = mandoc_strdup(ln.buf);
		thisln->sz = strlen(ln.buf) + 1;
		thisln->next = NULL;
		if (firstln == NULL) {
			firstln = lastln = thisln;
			if (curp->secondary == NULL)
				curp->secondary = firstln;
		} else {
			lastln->next = thisln;
			lastln = thisln;
		}

		/* XXX Ugly hack to mark the end of the input. */

		if (i == blk.sz || blk.buf[i] == '\0') {
			if (pos + 2 > ln.sz)
				resize_buf(&ln, 256);
			ln.buf[pos++] = '\n';
			ln.buf[pos] = '\0';
		}

		/*
		 * A significant amount of complexity is contained by
		 * the roff preprocessor.  It's line-oriented but can be
		 * expressed on one line, so we need at times to
		 * readjust our starting point and re-run it.  The roff
		 * preprocessor can also readjust the buffers with new
		 * data, so we pass them in wholesale.
		 */

		of = 0;
rerun:
		line_result = roff_parseln(curp->roff, curp->line, &ln, &of);

		/* Process options. */

		if (line_result & ROFF_APPEND)
			assert(line_result == (ROFF_IGN | ROFF_APPEND));

		if (line_result & ROFF_USERCALL)
			assert((line_result & ROFF_MASK) == ROFF_REPARSE);

		if (line_result & ROFF_USERRET) {
			assert(line_result == (ROFF_IGN | ROFF_USERRET));
			if (start == 0) {
				/* Return from the current macro. */
				result = ROFF_USERRET;
				goto out;
			}
		}

		switch (line_result & ROFF_LOOPMASK) {
		case ROFF_IGN:
			break;
		case ROFF_WHILE:
			if (curp->loop != NULL) {
				if (loop == curp->loop)
					break;
				mandoc_msg(MANDOCERR_WHILE_NEST,
				    curp->line, pos, NULL);
			}
			curp->loop = thisln;
			loop = NULL;
			inloop = 1;
			break;
		case ROFF_LOOPCONT:
		case ROFF_LOOPEXIT:
			if (curp->loop == NULL) {
				mandoc_msg(MANDOCERR_WHILE_FAIL,
				    curp->line, pos, NULL);
				break;
			}
			if (inloop == 0) {
				mandoc_msg(MANDOCERR_WHILE_INTO,
				    curp->line, pos, NULL);
				curp->loop = loop = NULL;
				break;
			}
			if (line_result & ROFF_LOOPCONT)
				loop = curp->loop;
			else {
				curp->loop = loop = NULL;
				inloop = 0;
			}
			break;
		default:
			abort();
		}

		/* Process the main instruction from the roff parser. */

		switch (line_result & ROFF_MASK) {
		case ROFF_IGN:
			break;
		case ROFF_CONT:
			if (curp->man->meta.macroset == MACROSET_NONE)
				choose_parser(curp);
			if ((curp->man->meta.macroset == MACROSET_MDOC ?
			     mdoc_parseln(curp->man, curp->line, ln.buf, of) :
			     man_parseln(curp->man, curp->line, ln.buf, of)
			    ) == 2)
				goto out;
			break;
		case ROFF_RERUN:
			goto rerun;
		case ROFF_REPARSE:
			if (++curp->reparse_count > REPARSE_LIMIT) {
				/* Abort and return to the top level. */
				result = ROFF_IGN;
				mandoc_msg(MANDOCERR_ROFFLOOP,
				    curp->line, pos, NULL);
				goto out;
			}
			result = mparse_buf_r(curp, ln, of, 0);
			if (line_result & ROFF_USERCALL) {
				roff_userret(curp->roff);
				/* Continue normally. */
				if (result & ROFF_USERRET)
					result = ROFF_CONT;
			}
			if (start == 0 && result != ROFF_CONT)
				goto out;
			break;
		case ROFF_SO:
			if ( ! (curp->options & MPARSE_SO) &&
			    (i >= blk.sz || blk.buf[i] == '\0')) {
				curp->man->meta.sodest =
				    mandoc_strdup(ln.buf + of);
				goto out;
			}
			if ((fd = mparse_open(curp, ln.buf + of)) != -1) {
				mparse_readfd(curp, fd, ln.buf + of);
				close(fd);
			} else {
				mandoc_msg(MANDOCERR_SO_FAIL,
				    curp->line, of, ".so %s: %s",
				    ln.buf + of, strerror(errno));
				ln.sz = mandoc_asprintf(&cp,
				    ".sp\nSee the file %s.\n.sp",
				    ln.buf + of);
				free(ln.buf);
				ln.buf = cp;
				of = 0;
				mparse_buf_r(curp, ln, of, 0);
			}
			break;
		default:
			abort();
		}

		/* Start the next input line. */

		if (loop != NULL &&
		    (line_result & ROFF_LOOPMASK) == ROFF_IGN)
			loop = loop->next;

		if (loop != NULL) {
			if ((line_result & ROFF_APPEND) == 0)
				*ln.buf = '\0';
			if (ln.sz < loop->sz)
				resize_buf(&ln, loop->sz);
			(void)strlcat(ln.buf, loop->buf, ln.sz);
			of = 0;
			goto rerun;
		}

		pos = (line_result & ROFF_APPEND) ? strlen(ln.buf) : 0;
	}
out:
	if (inloop) {
		if (result != ROFF_USERRET)
			mandoc_msg(MANDOCERR_WHILE_OUTOF,
			    curp->line, pos, NULL);
		curp->loop = NULL;
	}
	free(ln.buf);
	if (firstln != curp->secondary)
		free_buf_list(firstln);
	return result;
}