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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {unsigned char* cstr; int /*<<< orphan*/ * wstr; } ;
struct bwstring {int len; TYPE_1__ data; } ;

/* Variables and functions */
 int BWSLEN (struct bwstring*) ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  bws_setlen (struct bwstring*,size_t) ; 
 scalar_t__ isblank (unsigned char) ; 
 scalar_t__ iswblank (int /*<<< orphan*/ ) ; 

struct bwstring *
ignore_leading_blanks(struct bwstring *str)
{

	if (MB_CUR_MAX == 1) {
		unsigned char *dst, *end, *src;

		src = str->data.cstr;
		dst = src;
		end = src + str->len;

		while (src < end && isblank(*src))
			++src;

		if (src != dst) {
			size_t newlen;

			newlen = BWSLEN(str) - (src - dst);

			while (src < end) {
				*dst = *src;
				++dst;
				++src;
			}
			bws_setlen(str, newlen);
		}
	} else {
		wchar_t *dst, *end, *src;

		src = str->data.wstr;
		dst = src;
		end = src + str->len;

		while (src < end && iswblank(*src))
			++src;

		if (src != dst) {

			size_t newlen = BWSLEN(str) - (src - dst);

			while (src < end) {
				*dst = *src;
				++dst;
				++src;
			}
			bws_setlen(str, newlen);

		}
	}
	return (str);
}