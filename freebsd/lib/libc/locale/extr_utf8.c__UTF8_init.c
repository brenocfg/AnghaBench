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
 int /*<<< orphan*/  _UTF8_mbrtowc ; 
 int /*<<< orphan*/  _UTF8_mbsinit ; 
 int /*<<< orphan*/  _UTF8_mbsnrtowcs ; 
 int /*<<< orphan*/  _UTF8_wcrtomb ; 
 int /*<<< orphan*/  _UTF8_wcsnrtombs ; 

int
_UTF8_init(struct xlocale_ctype *l, _RuneLocale *rl)
{

	l->__mbrtowc = _UTF8_mbrtowc;
	l->__wcrtomb = _UTF8_wcrtomb;
	l->__mbsinit = _UTF8_mbsinit;
	l->__mbsnrtowcs = _UTF8_mbsnrtowcs;
	l->__wcsnrtombs = _UTF8_wcsnrtombs;
	l->runes = rl;
	l->__mb_cur_max = 4;
	/*
	 * UCS-4 encoding used as the internal representation, so
	 * slots 0x0080-0x00FF are occuped and must be excluded
	 * from the single byte ctype by setting the limit.
	 */
	l->__mb_sb_limit = 128;

	return (0);
}