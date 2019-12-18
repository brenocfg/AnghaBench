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
typedef  int /*<<< orphan*/  uint32_t ;
struct archive_string_conv {int flag; } ;
struct archive_string {size_t length; char* s; int buffer_length; } ;

/* Variables and functions */
 int SCONV_FROM_UTF16BE ; 
 int SCONV_FROM_UTF16LE ; 
 int SCONV_TO_UTF16BE ; 
 int SCONV_TO_UTF16LE ; 
 int SCONV_TO_UTF8 ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int cesu8_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t unicode_to_utf16be (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t unicode_to_utf16le (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t unicode_to_utf8 (char*,size_t,int /*<<< orphan*/ ) ; 
 int utf16be_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 
 int utf16le_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int
archive_string_append_unicode(struct archive_string *as, const void *_p,
    size_t len, struct archive_string_conv *sc)
{
	const char *s;
	char *p, *endp;
	uint32_t uc;
	size_t w;
	int n, ret = 0, ts, tm;
	int (*parse)(uint32_t *, const char *, size_t);
	size_t (*unparse)(char *, size_t, uint32_t);

	if (sc->flag & SCONV_TO_UTF16BE) {
		unparse = unicode_to_utf16be;
		ts = 2;
	} else if (sc->flag & SCONV_TO_UTF16LE) {
		unparse = unicode_to_utf16le;
		ts = 2;
	} else if (sc->flag & SCONV_TO_UTF8) {
		unparse = unicode_to_utf8;
		ts = 1;
	} else {
		/*
		 * This case is going to be converted to another
		 * character-set through iconv.
		 */
		if (sc->flag & SCONV_FROM_UTF16BE) {
			unparse = unicode_to_utf16be;
			ts = 2;
		} else if (sc->flag & SCONV_FROM_UTF16LE) {
			unparse = unicode_to_utf16le;
			ts = 2;
		} else {
			unparse = unicode_to_utf8;
			ts = 1;
		}
	}

	if (sc->flag & SCONV_FROM_UTF16BE) {
		parse = utf16be_to_unicode;
		tm = 1;
	} else if (sc->flag & SCONV_FROM_UTF16LE) {
		parse = utf16le_to_unicode;
		tm = 1;
	} else {
		parse = cesu8_to_unicode;
		tm = ts;
	}

	if (archive_string_ensure(as, as->length + len * tm + ts) == NULL)
		return (-1);

	s = (const char *)_p;
	p = as->s + as->length;
	endp = as->s + as->buffer_length - ts;
	while ((n = parse(&uc, s, len)) != 0) {
		if (n < 0) {
			/* Use a replaced unicode character. */
			n *= -1;
			ret = -1;
		}
		s += n;
		len -= n;
		while ((w = unparse(p, endp - p, uc)) == 0) {
			/* There is not enough output buffer so
			 * we have to expand it. */
			as->length = p - as->s;
			if (archive_string_ensure(as,
			    as->buffer_length + len * tm + ts) == NULL)
				return (-1);
			p = as->s + as->length;
			endp = as->s + as->buffer_length - ts;
		}
		p += w;
	}
	as->length = p - as->s;
	as->s[as->length] = '\0';
	if (ts == 2)
		as->s[as->length+1] = '\0';
	return (ret);
}