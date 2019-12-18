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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int mbtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
conv_mbtowc(wchar_t *wc, const char *c, const wchar_t def)
{

	if (wc && c) {
		int res;

		res = mbtowc(wc, c, MB_CUR_MAX);
		if (res < 1)
			*wc = def;
	}
}