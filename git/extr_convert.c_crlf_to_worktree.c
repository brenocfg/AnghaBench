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
struct text_stat {scalar_t__ lonelf; } ;
struct strbuf {char const* buf; } ;
typedef  enum crlf_action { ____Placeholder_crlf_action } crlf_action ;

/* Variables and functions */
 scalar_t__ EOL_CRLF ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gather_stats (char const*,size_t,struct text_stat*) ; 
 char* memchr (char const*,char,size_t) ; 
 scalar_t__ output_eol (int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  will_convert_lf_to_crlf (struct text_stat*,int) ; 

__attribute__((used)) static int crlf_to_worktree(const char *src, size_t len,
			    struct strbuf *buf, enum crlf_action crlf_action)
{
	char *to_free = NULL;
	struct text_stat stats;

	if (!len || output_eol(crlf_action) != EOL_CRLF)
		return 0;

	gather_stats(src, len, &stats);
	if (!will_convert_lf_to_crlf(&stats, crlf_action))
		return 0;

	/* are we "faking" in place editing ? */
	if (src == buf->buf)
		to_free = strbuf_detach(buf, NULL);

	strbuf_grow(buf, len + stats.lonelf);
	for (;;) {
		const char *nl = memchr(src, '\n', len);
		if (!nl)
			break;
		if (nl > src && nl[-1] == '\r') {
			strbuf_add(buf, src, nl + 1 - src);
		} else {
			strbuf_add(buf, src, nl - src);
			strbuf_addstr(buf, "\r\n");
		}
		len -= nl + 1 - src;
		src  = nl + 1;
	}
	strbuf_add(buf, src, len);

	free(to_free);
	return 1;
}