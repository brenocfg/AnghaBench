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
 int /*<<< orphan*/  _GBK_mbrtowc ; 
 int /*<<< orphan*/  _GBK_mbsinit ; 
 int /*<<< orphan*/  _GBK_mbsnrtowcs ; 
 int /*<<< orphan*/  _GBK_wcrtomb ; 
 int /*<<< orphan*/  _GBK_wcsnrtombs ; 

int
_GBK_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->__mbrtowc = _GBK_mbrtowc;
	l->__wcrtomb = _GBK_wcrtomb;
	l->__mbsinit = _GBK_mbsinit;
	l->__mbsnrtowcs = _GBK_mbsnrtowcs;
	l->__wcsnrtombs = _GBK_wcsnrtombs;
	l->runes = rl;
	l->__mb_cur_max = 2;
	l->__mb_sb_limit = 128;
	return (0);
}