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
struct archive_string_conv {int dummy; } ;
struct archive_string {size_t length; char* s; int buffer_length; } ;

/* Variables and functions */
 scalar_t__ IS_SURROGATE_PAIR_LA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int cesu8_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 size_t unicode_to_utf8 (char*,int,int /*<<< orphan*/ ) ; 
 int utf8_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int
strncat_from_utf8_to_utf8(struct archive_string *as, const void *_p,
    size_t len, struct archive_string_conv *sc)
{
	const char *s;
	char *p, *endp;
	int n, ret = 0;

	(void)sc; /* UNUSED */

	if (archive_string_ensure(as, as->length + len + 1) == NULL)
		return (-1);

	s = (const char *)_p;
	p = as->s + as->length;
	endp = as->s + as->buffer_length -1;
	do {
		uint32_t uc;
		const char *ss = s;
		size_t w;

		/*
		 * Forward byte sequence until a conversion of that is needed.
		 */
		while ((n = utf8_to_unicode(&uc, s, len)) > 0) {
			s += n;
			len -= n;
		}
		if (ss < s) {
			if (p + (s - ss) > endp) {
				as->length = p - as->s;
				if (archive_string_ensure(as,
				    as->buffer_length + len + 1) == NULL)
					return (-1);
				p = as->s + as->length;
				endp = as->s + as->buffer_length -1;
			}

			memcpy(p, ss, s - ss);
			p += s - ss;
		}

		/*
		 * If n is negative, current byte sequence needs a replacement.
		 */
		if (n < 0) {
			if (n == -3 && IS_SURROGATE_PAIR_LA(uc)) {
				/* Current byte sequence may be CESU-8. */
				n = cesu8_to_unicode(&uc, s, len);
			}
			if (n < 0) {
				ret = -1;
				n *= -1;/* Use a replaced unicode character. */
			}

			/* Rebuild UTF-8 byte sequence. */
			while ((w = unicode_to_utf8(p, endp - p, uc)) == 0) {
				as->length = p - as->s;
				if (archive_string_ensure(as,
				    as->buffer_length + len + 1) == NULL)
					return (-1);
				p = as->s + as->length;
				endp = as->s + as->buffer_length -1;
			}
			p += w;
			s += n;
			len -= n;
		}
	} while (n > 0);
	as->length = p - as->s;
	as->s[as->length] = '\0';
	return (ret);
}