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
typedef  int uint32_t ;
struct archive_string_conv {int flag; } ;
struct archive_string {size_t length; char* s; int buffer_length; } ;

/* Variables and functions */
 void* CCC (int) ; 
 int FDC_MAX ; 
 int HC_LBASE ; 
 int HC_NCOUNT ; 
 int HC_SBASE ; 
 int HC_SCOUNT ; 
 int HC_TBASE ; 
 int HC_TCOUNT ; 
 int HC_VBASE ; 
 scalar_t__ IS_DECOMPOSABLE_BLOCK (int) ; 
 int /*<<< orphan*/  REPLACE_UC_WITH (int) ; 
 int SCONV_FROM_UTF16BE ; 
 int SCONV_FROM_UTF16LE ; 
 int SCONV_FROM_UTF8 ; 
 int SCONV_TO_UTF16BE ; 
 int SCONV_TO_UTF16LE ; 
 int SCONV_TO_UTF8 ; 
 int /*<<< orphan*/  UNPARSE (char*,char*,int) ; 
 int /*<<< orphan*/  WRITE_UC () ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int cesu8_to_unicode (int*,char const*,size_t) ; 
 scalar_t__ get_nfd (int*,int*,int) ; 
 size_t unicode_to_utf16be (char*,size_t,int) ; 
 size_t unicode_to_utf16le (char*,size_t,int) ; 
 size_t unicode_to_utf8 (char*,size_t,int) ; 
 int utf16be_to_unicode (int*,char const*,size_t) ; 
 int utf16le_to_unicode (int*,char const*,size_t) ; 

__attribute__((used)) static int
archive_string_normalize_D(struct archive_string *as, const void *_p,
    size_t len, struct archive_string_conv *sc)
{
	const char *s = (const char *)_p;
	char *p, *endp;
	uint32_t uc, uc2;
	size_t w;
	int always_replace, n, n2, ret = 0, spair, ts, tm;
	int (*parse)(uint32_t *, const char *, size_t);
	size_t (*unparse)(char *, size_t, uint32_t);

	always_replace = 1;
	ts = 1;/* text size. */
	if (sc->flag & SCONV_TO_UTF16BE) {
		unparse = unicode_to_utf16be;
		ts = 2;
		if (sc->flag & SCONV_FROM_UTF16BE)
			always_replace = 0;
	} else if (sc->flag & SCONV_TO_UTF16LE) {
		unparse = unicode_to_utf16le;
		ts = 2;
		if (sc->flag & SCONV_FROM_UTF16LE)
			always_replace = 0;
	} else if (sc->flag & SCONV_TO_UTF8) {
		unparse = unicode_to_utf8;
		if (sc->flag & SCONV_FROM_UTF8)
			always_replace = 0;
	} else {
		/*
		 * This case is going to be converted to another
		 * character-set through iconv.
		 */
		always_replace = 0;
		if (sc->flag & SCONV_FROM_UTF16BE) {
			unparse = unicode_to_utf16be;
			ts = 2;
		} else if (sc->flag & SCONV_FROM_UTF16LE) {
			unparse = unicode_to_utf16le;
			ts = 2;
		} else {
			unparse = unicode_to_utf8;
		}
	}

	if (sc->flag & SCONV_FROM_UTF16BE) {
		parse = utf16be_to_unicode;
		tm = 1;
		spair = 4;/* surrogate pair size in UTF-16. */
	} else if (sc->flag & SCONV_FROM_UTF16LE) {
		parse = utf16le_to_unicode;
		tm = 1;
		spair = 4;/* surrogate pair size in UTF-16. */
	} else {
		parse = cesu8_to_unicode;
		tm = ts;
		spair = 6;/* surrogate pair size in UTF-8. */
	}

	if (archive_string_ensure(as, as->length + len * tm + ts) == NULL)
		return (-1);

	p = as->s + as->length;
	endp = as->s + as->buffer_length - ts;
	while ((n = parse(&uc, s, len)) != 0) {
		const char *ucptr;
		uint32_t cp1, cp2;
		int SIndex;
		struct {
			uint32_t uc;
			int ccc;
		} fdc[FDC_MAX];
		int fdi, fdj;
		int ccc;

check_first_code:
		if (n < 0) {
			/* Use a replaced unicode character. */
			UNPARSE(p, endp, uc);
			s += n*-1;
			len -= n*-1;
			ret = -1;
			continue;
		} else if (n == spair || always_replace)
			/* uc is converted from a surrogate pair.
			 * this should be treated as a changed code. */
			ucptr = NULL;
		else
			ucptr = s;
		s += n;
		len -= n;

		/* Hangul Decomposition. */
		if ((SIndex = uc - HC_SBASE) >= 0 && SIndex < HC_SCOUNT) {
			int L = HC_LBASE + SIndex / HC_NCOUNT;
			int V = HC_VBASE + (SIndex % HC_NCOUNT) / HC_TCOUNT;
			int T = HC_TBASE + SIndex % HC_TCOUNT;

			REPLACE_UC_WITH(L);
			WRITE_UC();
			REPLACE_UC_WITH(V);
			WRITE_UC();
			if (T != HC_TBASE) {
				REPLACE_UC_WITH(T);
				WRITE_UC();
			}
			continue;
		}
		if (IS_DECOMPOSABLE_BLOCK(uc) && CCC(uc) != 0) {
			WRITE_UC();
			continue;
		}

		fdi = 0;
		while (get_nfd(&cp1, &cp2, uc) && fdi < FDC_MAX) {
			int k;

			for (k = fdi; k > 0; k--)
				fdc[k] = fdc[k-1];
			fdc[0].ccc = CCC(cp2);
			fdc[0].uc = cp2;
			fdi++;
			REPLACE_UC_WITH(cp1);
		}

		/* Read following code points. */
		while ((n2 = parse(&uc2, s, len)) > 0 &&
		    (ccc = CCC(uc2)) != 0 && fdi < FDC_MAX) {
			int j, k;

			s += n2;
			len -= n2;
			for (j = 0; j < fdi; j++) {
				if (fdc[j].ccc > ccc)
					break;
			}
			if (j < fdi) {
				for (k = fdi; k > j; k--)
					fdc[k] = fdc[k-1];
				fdc[j].ccc = ccc;
				fdc[j].uc = uc2;
			} else {
				fdc[fdi].ccc = ccc;
				fdc[fdi].uc = uc2;
			}
			fdi++;
		}

		WRITE_UC();
		for (fdj = 0; fdj < fdi; fdj++) {
			REPLACE_UC_WITH(fdc[fdj].uc);
			WRITE_UC();
		}

		if (n2 == 0)
			break;
		REPLACE_UC_WITH(uc2);
		n = n2;
		goto check_first_code;
	}
	as->length = p - as->s;
	as->s[as->length] = '\0';
	if (ts == 2)
		as->s[as->length+1] = '\0';
	return (ret);
}