#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct xlocale_collate {scalar_t__ __collate_load_error; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_4__ {scalar_t__* components; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (TYPE_1__*) ; 
 size_t XLC_COLLATE ; 
 size_t _collate_wxfrm (struct xlocale_collate*,int const*,int*,size_t) ; 
 int /*<<< orphan*/  wcscpy (int*,int const*) ; 
 size_t wcslen (int const*) ; 
 int /*<<< orphan*/  wcsncpy (int*,int const*,size_t) ; 

size_t
wcsxfrm_l(wchar_t * __restrict dest, const wchar_t * __restrict src, size_t len, locale_t locale)
{
	size_t slen;
	FIX_LOCALE(locale);
	struct xlocale_collate *table =
		(struct xlocale_collate*)locale->components[XLC_COLLATE];

	if (*src == L'\0') {
		if (len != 0)
			*dest = L'\0';
		return (0);
	}

	if ((table->__collate_load_error) ||
	    ((slen = _collate_wxfrm(table, src, dest, len)) == (size_t)-1)) {
		goto error;
	}

	/* Add null termination at the correct location. */
	if (len > slen) {
		dest[slen] = 0;
	} else if (len) {
		dest[len-1] = 0;
	}

	return (slen);

error:
	slen = wcslen(src);
	if (slen < len)
		(void) wcscpy(dest, src);
	else if (len > 0) {
		(void) wcsncpy(dest, src, len - 1);
		dest[len - 1] = L'\0';
	}
	return (slen);
}