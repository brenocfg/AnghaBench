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
struct xlocale_ctype {int __mb_cur_max; int __mb_sb_limit; int /*<<< orphan*/ * runes; int /*<<< orphan*/  __mbsinit; int /*<<< orphan*/  __wcsnrtombs; int /*<<< orphan*/  __mbsnrtowcs; int /*<<< orphan*/  __wcrtomb; int /*<<< orphan*/  __mbrtowc; } ;
typedef  int /*<<< orphan*/  _RuneLocale ;

/* Variables and functions */
 int /*<<< orphan*/  _MSKanji_mbrtowc ; 
 int /*<<< orphan*/  _MSKanji_mbsinit ; 
 int /*<<< orphan*/  _MSKanji_mbsnrtowcs ; 
 int /*<<< orphan*/  _MSKanji_wcrtomb ; 
 int /*<<< orphan*/  _MSKanji_wcsnrtombs ; 

int
_MSKanji_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->__mbrtowc = _MSKanji_mbrtowc;
	l->__wcrtomb = _MSKanji_wcrtomb;
	l->__mbsnrtowcs = _MSKanji_mbsnrtowcs;
	l->__wcsnrtombs = _MSKanji_wcsnrtombs;
	l->__mbsinit = _MSKanji_mbsinit;
	l->runes = rl;
	l->__mb_cur_max = 2;
	l->__mb_sb_limit = 224;
	return (0);
}