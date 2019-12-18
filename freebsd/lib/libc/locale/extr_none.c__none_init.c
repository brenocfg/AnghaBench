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
struct xlocale_ctype {int __mb_cur_max; int __mb_sb_limit; int /*<<< orphan*/ * runes; int /*<<< orphan*/  __wcsnrtombs; int /*<<< orphan*/  __wcrtomb; int /*<<< orphan*/  __mbsnrtowcs; int /*<<< orphan*/  __mbsinit; int /*<<< orphan*/  __mbrtowc; } ;
typedef  int /*<<< orphan*/  _RuneLocale ;

/* Variables and functions */
 int /*<<< orphan*/  _none_mbrtowc ; 
 int /*<<< orphan*/  _none_mbsinit ; 
 int /*<<< orphan*/  _none_mbsnrtowcs ; 
 int /*<<< orphan*/  _none_wcrtomb ; 
 int /*<<< orphan*/  _none_wcsnrtombs ; 

int
_none_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->__mbrtowc = _none_mbrtowc;
	l->__mbsinit = _none_mbsinit;
	l->__mbsnrtowcs = _none_mbsnrtowcs;
	l->__wcrtomb = _none_wcrtomb;
	l->__wcsnrtombs = _none_wcsnrtombs;
	l->runes = rl;
	l->__mb_cur_max = 1;
	l->__mb_sb_limit = 256;
	return(0);
}