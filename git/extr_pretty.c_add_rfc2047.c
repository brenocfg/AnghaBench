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
typedef  enum rfc2047_type { ____Placeholder_rfc2047_type } rfc2047_type ;

/* Variables and functions */
 scalar_t__ is_rfc2047_special (unsigned char const,int) ; 
 int last_line_length (struct strbuf*) ; 
 int mbs_chrlen (char const**,size_t*,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void add_rfc2047(struct strbuf *sb, const char *line, size_t len,
		       const char *encoding, enum rfc2047_type type)
{
	static const int max_encoded_length = 76; /* per rfc2047 */
	int i;
	int line_len = last_line_length(sb);

	strbuf_grow(sb, len * 3 + strlen(encoding) + 100);
	strbuf_addf(sb, "=?%s?q?", encoding);
	line_len += strlen(encoding) + 5; /* 5 for =??q? */

	while (len) {
		/*
		 * RFC 2047, section 5 (3):
		 *
		 * Each 'encoded-word' MUST represent an integral number of
		 * characters.  A multi-octet character may not be split across
		 * adjacent 'encoded- word's.
		 */
		const unsigned char *p = (const unsigned char *)line;
		int chrlen = mbs_chrlen(&line, &len, encoding);
		int is_special = (chrlen > 1) || is_rfc2047_special(*p, type);

		/* "=%02X" * chrlen, or the byte itself */
		const char *encoded_fmt = is_special ? "=%02X"    : "%c";
		int	    encoded_len = is_special ? 3 * chrlen : 1;

		/*
		 * According to RFC 2047, we could encode the special character
		 * ' ' (space) with '_' (underscore) for readability. But many
		 * programs do not understand this and just leave the
		 * underscore in place. Thus, we do nothing special here, which
		 * causes ' ' to be encoded as '=20', avoiding this problem.
		 */

		if (line_len + encoded_len + 2 > max_encoded_length) {
			/* It won't fit with trailing "?=" --- break the line */
			strbuf_addf(sb, "?=\n =?%s?q?", encoding);
			line_len = strlen(encoding) + 5 + 1; /* =??q? plus SP */
		}

		for (i = 0; i < chrlen; i++)
			strbuf_addf(sb, encoded_fmt, p[i]);
		line_len += encoded_len;
	}
	strbuf_addstr(sb, "?=");
}