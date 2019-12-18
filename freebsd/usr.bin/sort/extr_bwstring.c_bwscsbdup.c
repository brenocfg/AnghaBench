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
struct TYPE_2__ {unsigned char* wstr; int /*<<< orphan*/  cstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 struct bwstring* bwsalloc (size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 size_t mbrlen (char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t mbrtowc (unsigned char*,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct bwstring *
bwscsbdup(const unsigned char *str, size_t len)
{
	struct bwstring *ret;

	ret = bwsalloc(len);

	if (str) {
		if (MB_CUR_MAX == 1)
			memcpy(ret->data.cstr, str, len);
		else {
			mbstate_t mbs;
			const char *s;
			size_t charlen, chars, cptr;

			chars = 0;
			cptr = 0;
			s = (const char *) str;

			memset(&mbs, 0, sizeof(mbs));

			while (cptr < len) {
				size_t n = MB_CUR_MAX;

				if (n > len - cptr)
					n = len - cptr;
				charlen = mbrlen(s + cptr, n, &mbs);
				switch (charlen) {
				case 0:
					/* FALLTHROUGH */
				case (size_t) -1:
					/* FALLTHROUGH */
				case (size_t) -2:
					ret->data.wstr[chars++] =
					    (unsigned char) s[cptr];
					++cptr;
					break;
				default:
					n = mbrtowc(ret->data.wstr + (chars++),
					    s + cptr, charlen, &mbs);
					if ((n == (size_t)-1) || (n == (size_t)-2))
						/* NOTREACHED */
						err(2, "mbrtowc error");
					cptr += charlen;
				}
			}

			ret->len = chars;
			ret->data.wstr[ret->len] = L'\0';
		}
	}
	return (ret);
}