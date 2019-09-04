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

/* Variables and functions */
 int CONV_WRITE_OBJECT ; 
 char* _ (char*) ; 
 scalar_t__ check_roundtrip (char const*) ; 
 char const* default_encoding ; 
 int /*<<< orphan*/  die (char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  error (char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 char* reencode_string_len (char const*,size_t,char const*,char const*,size_t*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  trace_encoding (char*,char const*,char const*,char const*,size_t) ; 
 int /*<<< orphan*/  trace_printf (char*,char const*) ; 
 scalar_t__ validate_encoding (char const*,char const*,char const*,size_t,int) ; 

__attribute__((used)) static int encode_to_git(const char *path, const char *src, size_t src_len,
			 struct strbuf *buf, const char *enc, int conv_flags)
{
	char *dst;
	size_t dst_len;
	int die_on_error = conv_flags & CONV_WRITE_OBJECT;

	/*
	 * No encoding is specified or there is nothing to encode.
	 * Tell the caller that the content was not modified.
	 */
	if (!enc || (src && !src_len))
		return 0;

	/*
	 * Looks like we got called from "would_convert_to_git()".
	 * This means Git wants to know if it would encode (= modify!)
	 * the content. Let's answer with "yes", since an encoding was
	 * specified.
	 */
	if (!buf && !src)
		return 1;

	if (validate_encoding(path, enc, src, src_len, die_on_error))
		return 0;

	trace_encoding("source", path, enc, src, src_len);
	dst = reencode_string_len(src, src_len, default_encoding, enc,
				  &dst_len);
	if (!dst) {
		/*
		 * We could add the blob "as-is" to Git. However, on checkout
		 * we would try to reencode to the original encoding. This
		 * would fail and we would leave the user with a messed-up
		 * working tree. Let's try to avoid this by screaming loud.
		 */
		const char* msg = _("failed to encode '%s' from %s to %s");
		if (die_on_error)
			die(msg, path, enc, default_encoding);
		else {
			error(msg, path, enc, default_encoding);
			return 0;
		}
	}
	trace_encoding("destination", path, default_encoding, dst, dst_len);

	/*
	 * UTF supports lossless conversion round tripping [1] and conversions
	 * between UTF and other encodings are mostly round trip safe as
	 * Unicode aims to be a superset of all other character encodings.
	 * However, certain encodings (e.g. SHIFT-JIS) are known to have round
	 * trip issues [2]. Check the round trip conversion for all encodings
	 * listed in core.checkRoundtripEncoding.
	 *
	 * The round trip check is only performed if content is written to Git.
	 * This ensures that no information is lost during conversion to/from
	 * the internal UTF-8 representation.
	 *
	 * Please note, the code below is not tested because I was not able to
	 * generate a faulty round trip without an iconv error. Iconv errors
	 * are already caught above.
	 *
	 * [1] http://unicode.org/faq/utf_bom.html#gen2
	 * [2] https://support.microsoft.com/en-us/help/170559/prb-conversion-problem-between-shift-jis-and-unicode
	 */
	if (die_on_error && check_roundtrip(enc)) {
		char *re_src;
		size_t re_src_len;

		re_src = reencode_string_len(dst, dst_len,
					     enc, default_encoding,
					     &re_src_len);

		trace_printf("Checking roundtrip encoding for %s...\n", enc);
		trace_encoding("reencoded source", path, enc,
			       re_src, re_src_len);

		if (!re_src || src_len != re_src_len ||
		    memcmp(src, re_src, src_len)) {
			const char* msg = _("encoding '%s' from %s to %s and "
					    "back is not the same");
			die(msg, path, enc, default_encoding);
		}

		free(re_src);
	}

	strbuf_attach(buf, dst, dst_len, dst_len + 1);
	return 1;
}