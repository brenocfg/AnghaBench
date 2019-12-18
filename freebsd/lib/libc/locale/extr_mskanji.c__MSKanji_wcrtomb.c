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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_2__ {scalar_t__ ch; } ;
typedef  TYPE_1__ _MSKanjiState ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static size_t
_MSKanji_wcrtomb(char * __restrict s, wchar_t wc, mbstate_t * __restrict ps)
{
	_MSKanjiState *ms;
	int len, i;

	ms = (_MSKanjiState *)ps;

	if (ms->ch != 0) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	if (s == NULL)
		/* Reset to initial shift state (no-op) */
		return (1);
	len = (wc > 0x100) ? 2 : 1;
	for (i = len; i-- > 0; )
		*s++ = wc >> (i << 3);
	return (len);
}