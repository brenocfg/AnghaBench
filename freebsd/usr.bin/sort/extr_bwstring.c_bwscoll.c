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
typedef  scalar_t__ wchar_t ;
struct TYPE_2__ {unsigned char* cstr; scalar_t__* wstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 scalar_t__ byte_sort ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int memcmp (unsigned char const*,unsigned char const*,size_t) ; 
 int strcoll (char const*,char const*) ; 
 int wide_str_coll (scalar_t__ const*,scalar_t__ const*) ; 

int
bwscoll(const struct bwstring *bws1, const struct bwstring *bws2, size_t offset)
{
	size_t len1, len2;

	len1 = bws1->len;
	len2 = bws2->len;

	if (len1 <= offset)
		return ((len2 <= offset) ? 0 : -1);
	else {
		if (len2 <= offset)
			return (+1);
		else {
			len1 -= offset;
			len2 -= offset;

			if (MB_CUR_MAX == 1) {
				const unsigned char *s1, *s2;

				s1 = bws1->data.cstr + offset;
				s2 = bws2->data.cstr + offset;

				if (byte_sort) {
					int res = 0;

					if (len1 > len2) {
						res = memcmp(s1, s2, len2);
						if (!res)
							res = +1;
					} else if (len1 < len2) {
						res = memcmp(s1, s2, len1);
						if (!res)
							res = -1;
					} else
						res = memcmp(s1, s2, len1);

					return (res);

				} else {
					int res = 0;
					size_t i, maxlen;

					i = 0;
					maxlen = len1;

					if (maxlen > len2)
						maxlen = len2;

					while (i < maxlen) {
						/* goto next non-zero part: */
						while ((i < maxlen) &&
						    !s1[i] && !s2[i])
							++i;

						if (i >= maxlen)
							break;

						if (s1[i] == 0) {
							if (s2[i] == 0)
								/* NOTREACHED */
								err(2, "bwscoll error 01");
							else
								return (-1);
						} else if (s2[i] == 0)
							return (+1);

						res = strcoll((const char*)(s1 + i), (const char*)(s2 + i));
						if (res)
							return (res);

						while ((i < maxlen) &&
						    s1[i] && s2[i])
							++i;

						if (i >= maxlen)
							break;

						if (s1[i] == 0) {
							if (s2[i] == 0) {
								++i;
								continue;
							} else
								return (-1);
						} else if (s2[i] == 0)
							return (+1);
						else
							/* NOTREACHED */
							err(2, "bwscoll error 02");
					}

					if (len1 < len2)
						return (-1);
					else if (len1 > len2)
						return (+1);

					return (0);
				}
			} else {
				const wchar_t *s1, *s2;
				size_t i, maxlen;
				int res = 0;

				s1 = bws1->data.wstr + offset;
				s2 = bws2->data.wstr + offset;

				i = 0;
				maxlen = len1;

				if (maxlen > len2)
					maxlen = len2;

				while (i < maxlen) {

					/* goto next non-zero part: */
					while ((i < maxlen) &&
					    !s1[i] && !s2[i])
						++i;

					if (i >= maxlen)
						break;

					if (s1[i] == 0) {
						if (s2[i] == 0)
							/* NOTREACHED */
							err(2, "bwscoll error 1");
						else
							return (-1);
					} else if (s2[i] == 0)
						return (+1);

					res = wide_str_coll(s1 + i, s2 + i);
					if (res)
						return (res);

					while ((i < maxlen) && s1[i] && s2[i])
						++i;

					if (i >= maxlen)
						break;

					if (s1[i] == 0) {
						if (s2[i] == 0) {
							++i;
							continue;
						} else
							return (-1);
					} else if (s2[i] == 0)
						return (+1);
					else
						/* NOTREACHED */
						err(2, "bwscoll error 2");
				}

				if (len1 < len2)
					return (-1);
				else if (len1 > len2)
					return (+1);

				return (0);
			}
		}
	}
}