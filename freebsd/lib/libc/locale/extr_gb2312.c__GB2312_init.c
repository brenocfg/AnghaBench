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
struct xlocale_ctype {int __mb_cur_max; int __mb_sb_limit; int /*<<< orphan*/  __wcsnrtombs; int /*<<< orphan*/  __mbsnrtowcs; int /*<<< orphan*/  __mbsinit; int /*<<< orphan*/  __wcrtomb; int /*<<< orphan*/  __mbrtowc; int /*<<< orphan*/ * runes; } ;
typedef  int /*<<< orphan*/  _RuneLocale ;

/* Variables and functions */
 int /*<<< orphan*/  _GB2312_mbrtowc ; 
 int /*<<< orphan*/  _GB2312_mbsinit ; 
 int /*<<< orphan*/  _GB2312_mbsnrtowcs ; 
 int /*<<< orphan*/  _GB2312_wcrtomb ; 
 int /*<<< orphan*/  _GB2312_wcsnrtombs ; 

int
_GB2312_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->runes = rl;
	l->__mbrtowc = _GB2312_mbrtowc;
	l->__wcrtomb = _GB2312_wcrtomb;
	l->__mbsinit = _GB2312_mbsinit;
	l->__mbsnrtowcs = _GB2312_mbsnrtowcs;
	l->__wcsnrtombs = _GB2312_wcsnrtombs;
	l->__mb_cur_max = 2;
	l->__mb_sb_limit = 128;
	return (0);
}