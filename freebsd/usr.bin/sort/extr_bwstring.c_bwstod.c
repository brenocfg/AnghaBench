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
 int MB_CUR_MAX ; 
 scalar_t__ isblank (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 scalar_t__ iswblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iswprint (int /*<<< orphan*/ ) ; 
 double strtod (char*,char**) ; 
 double wcstod (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

double
bwstod(struct bwstring *s0, bool *empty)
{
	double ret = 0;

	if (MB_CUR_MAX == 1) {
		unsigned char *end, *s;
		char *ep;

		s = s0->data.cstr;
		end = s + s0->len;
		ep = NULL;

		while (isblank(*s) && s < end)
			++s;

		if (!isprint(*s)) {
			*empty = true;
			return (0);
		}

		ret = strtod((char*)s, &ep);
		if ((unsigned char*) ep == s) {
			*empty = true;
			return (0);
		}
	} else {
		wchar_t *end, *ep, *s;

		s = s0->data.wstr;
		end = s + s0->len;
		ep = NULL;

		while (iswblank(*s) && s < end)
			++s;

		if (!iswprint(*s)) {
			*empty = true;
			return (0);
		}

		ret = wcstod(s, &ep);
		if (ep == s) {
			*empty = true;
			return (0);
		}
	}

	*empty = false;
	return (ret);
}