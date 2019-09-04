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
struct strbuf {size_t len; char* buf; } ;
struct image {int nr; scalar_t__ len; char* buf; TYPE_1__* line; } ;
struct apply_state {scalar_t__ ws_error_action; scalar_t__ ws_ignore_action; } ;
struct TYPE_2__ {int flag; scalar_t__ hash; size_t len; } ;

/* Variables and functions */
 int LINE_COMMON ; 
 int LINE_PATCHED ; 
 unsigned int WS_BLANK_AT_EOF ; 
 scalar_t__ correct_ws_error ; 
 scalar_t__ ignore_ws_change ; 
 int /*<<< orphan*/  isspace (char) ; 
 int line_by_line_fuzzy_match (struct image*,struct image*,struct image*,unsigned long,int,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,scalar_t__) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_pre_post_images (struct image*,struct image*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  ws_fix_copy (struct strbuf*,char*,size_t,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_fragment(struct apply_state *state,
			  struct image *img,
			  struct image *preimage,
			  struct image *postimage,
			  unsigned long current,
			  int current_lno,
			  unsigned ws_rule,
			  int match_beginning, int match_end)
{
	int i;
	char *fixed_buf, *buf, *orig, *target;
	struct strbuf fixed;
	size_t fixed_len, postlen;
	int preimage_limit;

	if (preimage->nr + current_lno <= img->nr) {
		/*
		 * The hunk falls within the boundaries of img.
		 */
		preimage_limit = preimage->nr;
		if (match_end && (preimage->nr + current_lno != img->nr))
			return 0;
	} else if (state->ws_error_action == correct_ws_error &&
		   (ws_rule & WS_BLANK_AT_EOF)) {
		/*
		 * This hunk extends beyond the end of img, and we are
		 * removing blank lines at the end of the file.  This
		 * many lines from the beginning of the preimage must
		 * match with img, and the remainder of the preimage
		 * must be blank.
		 */
		preimage_limit = img->nr - current_lno;
	} else {
		/*
		 * The hunk extends beyond the end of the img and
		 * we are not removing blanks at the end, so we
		 * should reject the hunk at this position.
		 */
		return 0;
	}

	if (match_beginning && current_lno)
		return 0;

	/* Quick hash check */
	for (i = 0; i < preimage_limit; i++)
		if ((img->line[current_lno + i].flag & LINE_PATCHED) ||
		    (preimage->line[i].hash != img->line[current_lno + i].hash))
			return 0;

	if (preimage_limit == preimage->nr) {
		/*
		 * Do we have an exact match?  If we were told to match
		 * at the end, size must be exactly at current+fragsize,
		 * otherwise current+fragsize must be still within the preimage,
		 * and either case, the old piece should match the preimage
		 * exactly.
		 */
		if ((match_end
		     ? (current + preimage->len == img->len)
		     : (current + preimage->len <= img->len)) &&
		    !memcmp(img->buf + current, preimage->buf, preimage->len))
			return 1;
	} else {
		/*
		 * The preimage extends beyond the end of img, so
		 * there cannot be an exact match.
		 *
		 * There must be one non-blank context line that match
		 * a line before the end of img.
		 */
		char *buf_end;

		buf = preimage->buf;
		buf_end = buf;
		for (i = 0; i < preimage_limit; i++)
			buf_end += preimage->line[i].len;

		for ( ; buf < buf_end; buf++)
			if (!isspace(*buf))
				break;
		if (buf == buf_end)
			return 0;
	}

	/*
	 * No exact match. If we are ignoring whitespace, run a line-by-line
	 * fuzzy matching. We collect all the line length information because
	 * we need it to adjust whitespace if we match.
	 */
	if (state->ws_ignore_action == ignore_ws_change)
		return line_by_line_fuzzy_match(img, preimage, postimage,
						current, current_lno, preimage_limit);

	if (state->ws_error_action != correct_ws_error)
		return 0;

	/*
	 * The hunk does not apply byte-by-byte, but the hash says
	 * it might with whitespace fuzz. We weren't asked to
	 * ignore whitespace, we were asked to correct whitespace
	 * errors, so let's try matching after whitespace correction.
	 *
	 * While checking the preimage against the target, whitespace
	 * errors in both fixed, we count how large the corresponding
	 * postimage needs to be.  The postimage prepared by
	 * apply_one_fragment() has whitespace errors fixed on added
	 * lines already, but the common lines were propagated as-is,
	 * which may become longer when their whitespace errors are
	 * fixed.
	 */

	/* First count added lines in postimage */
	postlen = 0;
	for (i = 0; i < postimage->nr; i++) {
		if (!(postimage->line[i].flag & LINE_COMMON))
			postlen += postimage->line[i].len;
	}

	/*
	 * The preimage may extend beyond the end of the file,
	 * but in this loop we will only handle the part of the
	 * preimage that falls within the file.
	 */
	strbuf_init(&fixed, preimage->len + 1);
	orig = preimage->buf;
	target = img->buf + current;
	for (i = 0; i < preimage_limit; i++) {
		size_t oldlen = preimage->line[i].len;
		size_t tgtlen = img->line[current_lno + i].len;
		size_t fixstart = fixed.len;
		struct strbuf tgtfix;
		int match;

		/* Try fixing the line in the preimage */
		ws_fix_copy(&fixed, orig, oldlen, ws_rule, NULL);

		/* Try fixing the line in the target */
		strbuf_init(&tgtfix, tgtlen);
		ws_fix_copy(&tgtfix, target, tgtlen, ws_rule, NULL);

		/*
		 * If they match, either the preimage was based on
		 * a version before our tree fixed whitespace breakage,
		 * or we are lacking a whitespace-fix patch the tree
		 * the preimage was based on already had (i.e. target
		 * has whitespace breakage, the preimage doesn't).
		 * In either case, we are fixing the whitespace breakages
		 * so we might as well take the fix together with their
		 * real change.
		 */
		match = (tgtfix.len == fixed.len - fixstart &&
			 !memcmp(tgtfix.buf, fixed.buf + fixstart,
					     fixed.len - fixstart));

		/* Add the length if this is common with the postimage */
		if (preimage->line[i].flag & LINE_COMMON)
			postlen += tgtfix.len;

		strbuf_release(&tgtfix);
		if (!match)
			goto unmatch_exit;

		orig += oldlen;
		target += tgtlen;
	}


	/*
	 * Now handle the lines in the preimage that falls beyond the
	 * end of the file (if any). They will only match if they are
	 * empty or only contain whitespace (if WS_BLANK_AT_EOL is
	 * false).
	 */
	for ( ; i < preimage->nr; i++) {
		size_t fixstart = fixed.len; /* start of the fixed preimage */
		size_t oldlen = preimage->line[i].len;
		int j;

		/* Try fixing the line in the preimage */
		ws_fix_copy(&fixed, orig, oldlen, ws_rule, NULL);

		for (j = fixstart; j < fixed.len; j++)
			if (!isspace(fixed.buf[j]))
				goto unmatch_exit;

		orig += oldlen;
	}

	/*
	 * Yes, the preimage is based on an older version that still
	 * has whitespace breakages unfixed, and fixing them makes the
	 * hunk match.  Update the context lines in the postimage.
	 */
	fixed_buf = strbuf_detach(&fixed, &fixed_len);
	if (postlen < postimage->len)
		postlen = 0;
	update_pre_post_images(preimage, postimage,
			       fixed_buf, fixed_len, postlen);
	return 1;

 unmatch_exit:
	strbuf_release(&fixed);
	return 0;
}