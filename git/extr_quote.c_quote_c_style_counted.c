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
struct strbuf {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT (char) ; 
 int /*<<< orphan*/  EMITBUF (char const*,size_t) ; 
 size_t next_quote_pos (char const*,size_t) ; 
 char* sq_lookup ; 

__attribute__((used)) static size_t quote_c_style_counted(const char *name, ssize_t maxlen,
				    struct strbuf *sb, FILE *fp, int no_dq)
{
#undef EMIT
#define EMIT(c)                                 \
	do {                                        \
		if (sb) strbuf_addch(sb, (c));          \
		if (fp) fputc((c), fp);                 \
		count++;                                \
	} while (0)
#define EMITBUF(s, l)                           \
	do {                                        \
		if (sb) strbuf_add(sb, (s), (l));       \
		if (fp) fwrite((s), (l), 1, fp);        \
		count += (l);                           \
	} while (0)

	size_t len, count = 0;
	const char *p = name;

	for (;;) {
		int ch;

		len = next_quote_pos(p, maxlen);
		if (len == maxlen || (maxlen < 0 && !p[len]))
			break;

		if (!no_dq && p == name)
			EMIT('"');

		EMITBUF(p, len);
		EMIT('\\');
		p += len;
		ch = (unsigned char)*p++;
		if (maxlen >= 0)
			maxlen -= len + 1;
		if (sq_lookup[ch] >= ' ') {
			EMIT(sq_lookup[ch]);
		} else {
			EMIT(((ch >> 6) & 03) + '0');
			EMIT(((ch >> 3) & 07) + '0');
			EMIT(((ch >> 0) & 07) + '0');
		}
	}

	EMITBUF(p, len);
	if (p == name)   /* no ending quote needed */
		return 0;

	if (!no_dq)
		EMIT('"');
	return count;
}