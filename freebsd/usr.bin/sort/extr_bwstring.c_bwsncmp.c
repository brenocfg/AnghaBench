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
typedef  unsigned char wchar_t ;
struct TYPE_2__ {unsigned char* cstr; unsigned char* wstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 size_t SIZEOF_WCHAR_STRING (size_t) ; 
 int memcmp (unsigned char const*,unsigned char const*,size_t) ; 

int
bwsncmp(const struct bwstring *bws1, const struct bwstring *bws2,
    size_t offset, size_t len)
{
	size_t cmp_len, len1, len2;
	int res = 0;

	len1 = bws1->len;
	len2 = bws2->len;

	if (len1 <= offset) {
		return ((len2 <= offset) ? 0 : -1);
	} else {
		if (len2 <= offset)
			return (+1);
		else {
			len1 -= offset;
			len2 -= offset;

			cmp_len = len1;

			if (len2 < cmp_len)
				cmp_len = len2;

			if (len < cmp_len)
				cmp_len = len;

			if (MB_CUR_MAX == 1) {
				const unsigned char *s1, *s2;

				s1 = bws1->data.cstr + offset;
				s2 = bws2->data.cstr + offset;

				res = memcmp(s1, s2, cmp_len);

			} else {
				const wchar_t *s1, *s2;

				s1 = bws1->data.wstr + offset;
				s2 = bws2->data.wstr + offset;

				res = memcmp(s1, s2, SIZEOF_WCHAR_STRING(cmp_len));
			}
		}
	}

	if (res == 0) {
		if (len1 < cmp_len && len1 < len2)
			res = -1;
		else if (len2 < cmp_len && len2 < len1)
			res = +1;
	}

	return (res);
}