#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  runes; int /*<<< orphan*/  __mb_sb_limit; int /*<<< orphan*/  __mb_cur_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CurrentRuneLocale ; 
 int _LDP_ERROR ; 
 int _LDP_LOADED ; 
 int /*<<< orphan*/  __mb_cur_max ; 
 int /*<<< orphan*/  __mb_sb_limit ; 
 int __setrunelocale (TYPE_1__*,char const*) ; 
 TYPE_1__ __xlocale_global_ctype ; 
 int errno ; 

int
__wrap_setrunelocale(const char *locale)
{
	int ret = __setrunelocale(&__xlocale_global_ctype, locale);

	if (ret != 0) {
		errno = ret;
		return (_LDP_ERROR);
	}
	__mb_cur_max = __xlocale_global_ctype.__mb_cur_max;
	__mb_sb_limit = __xlocale_global_ctype.__mb_sb_limit;
	_CurrentRuneLocale = __xlocale_global_ctype.runes;
	return (_LDP_LOADED);
}