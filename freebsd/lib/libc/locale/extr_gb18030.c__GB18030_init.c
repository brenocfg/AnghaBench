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
struct xlocale_ctype {int __mb_cur_max; int __mb_sb_limit; int /*<<< orphan*/ * runes; int /*<<< orphan*/  __wcsnrtombs; int /*<<< orphan*/  __mbsnrtowcs; int /*<<< orphan*/  __mbsinit; int /*<<< orphan*/  __wcrtomb; int /*<<< orphan*/  __mbrtowc; } ;
typedef  int /*<<< orphan*/  _RuneLocale ;

/* Variables and functions */
 int /*<<< orphan*/  _GB18030_mbrtowc ; 
 int /*<<< orphan*/  _GB18030_mbsinit ; 
 int /*<<< orphan*/  _GB18030_mbsnrtowcs ; 
 int /*<<< orphan*/  _GB18030_wcrtomb ; 
 int /*<<< orphan*/  _GB18030_wcsnrtombs ; 

int
_GB18030_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->__mbrtowc = _GB18030_mbrtowc;
	l->__wcrtomb = _GB18030_wcrtomb;
	l->__mbsinit = _GB18030_mbsinit;
	l->__mbsnrtowcs = _GB18030_mbsnrtowcs;
	l->__wcsnrtombs = _GB18030_wcsnrtombs;
	l->runes = rl;
	l->__mb_cur_max = 4;
	l->__mb_sb_limit = 128;

	return (0);
}