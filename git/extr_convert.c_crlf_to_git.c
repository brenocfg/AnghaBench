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
struct text_stat {scalar_t__ lonelf; scalar_t__ crlf; } ;
struct strbuf {size_t len; char* buf; } ;
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  new_stats ;
typedef  enum crlf_action { ____Placeholder_crlf_action } crlf_action ;

/* Variables and functions */
 int CONV_EOL_RENORMALIZE ; 
 int CONV_EOL_RNDTRP_DIE ; 
 int CONV_EOL_RNDTRP_WARN ; 
 int CRLF_AUTO ; 
 int CRLF_AUTO_CRLF ; 
 int CRLF_AUTO_INPUT ; 
 int CRLF_BINARY ; 
 int /*<<< orphan*/  check_global_conv_flags_eol (char const*,int,struct text_stat*,struct text_stat*,int) ; 
 scalar_t__ convert_is_binary (struct text_stat*) ; 
 int /*<<< orphan*/  gather_stats (char const*,size_t,struct text_stat*) ; 
 scalar_t__ has_crlf_in_index (struct index_state const*,char const*) ; 
 int /*<<< orphan*/  memcpy (struct text_stat*,struct text_stat*,int) ; 
 size_t strbuf_avail (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 scalar_t__ will_convert_lf_to_crlf (struct text_stat*,int) ; 

__attribute__((used)) static int crlf_to_git(const struct index_state *istate,
		       const char *path, const char *src, size_t len,
		       struct strbuf *buf,
		       enum crlf_action crlf_action, int conv_flags)
{
	struct text_stat stats;
	char *dst;
	int convert_crlf_into_lf;

	if (crlf_action == CRLF_BINARY ||
	    (src && !len))
		return 0;

	/*
	 * If we are doing a dry-run and have no source buffer, there is
	 * nothing to analyze; we must assume we would convert.
	 */
	if (!buf && !src)
		return 1;

	gather_stats(src, len, &stats);
	/* Optimization: No CRLF? Nothing to convert, regardless. */
	convert_crlf_into_lf = !!stats.crlf;

	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		if (convert_is_binary(&stats))
			return 0;
		/*
		 * If the file in the index has any CR in it, do not
		 * convert.  This is the new safer autocrlf handling,
		 * unless we want to renormalize in a merge or
		 * cherry-pick.
		 */
		if ((!(conv_flags & CONV_EOL_RENORMALIZE)) &&
		    has_crlf_in_index(istate, path))
			convert_crlf_into_lf = 0;
	}
	if (((conv_flags & CONV_EOL_RNDTRP_WARN) ||
	     ((conv_flags & CONV_EOL_RNDTRP_DIE) && len))) {
		struct text_stat new_stats;
		memcpy(&new_stats, &stats, sizeof(new_stats));
		/* simulate "git add" */
		if (convert_crlf_into_lf) {
			new_stats.lonelf += new_stats.crlf;
			new_stats.crlf = 0;
		}
		/* simulate "git checkout" */
		if (will_convert_lf_to_crlf(&new_stats, crlf_action)) {
			new_stats.crlf += new_stats.lonelf;
			new_stats.lonelf = 0;
		}
		check_global_conv_flags_eol(path, crlf_action, &stats, &new_stats, conv_flags);
	}
	if (!convert_crlf_into_lf)
		return 0;

	/*
	 * At this point all of our source analysis is done, and we are sure we
	 * would convert. If we are in dry-run mode, we can give an answer.
	 */
	if (!buf)
		return 1;

	/* only grow if not in place */
	if (strbuf_avail(buf) + buf->len < len)
		strbuf_grow(buf, len - buf->len);
	dst = buf->buf;
	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		/*
		 * If we guessed, we already know we rejected a file with
		 * lone CR, and we can strip a CR without looking at what
		 * follow it.
		 */
		do {
			unsigned char c = *src++;
			if (c != '\r')
				*dst++ = c;
		} while (--len);
	} else {
		do {
			unsigned char c = *src++;
			if (! (c == '\r' && (1 < len && *src == '\n')))
				*dst++ = c;
		} while (--len);
	}
	strbuf_setlen(buf, dst - buf->buf);
	return 1;
}