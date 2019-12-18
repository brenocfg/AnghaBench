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
typedef  scalar_t__ wchar_t ;
typedef  int _wc_t ;
typedef  int _index_t ;
typedef  int _csid_t ;
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ _MSKanjiEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int MODE_JIS2004 ; 
 int /*<<< orphan*/  _mskanji1 (int) ; 
 int /*<<< orphan*/  _mskanji2 (int) ; 

__attribute__((used)) static __inline int
/*ARGSUSED*/
_citrus_MSKanji_stdenc_wctocs(_MSKanjiEncodingInfo * __restrict ei,
    _csid_t * __restrict csid, _index_t * __restrict idx, wchar_t wc)
{
	_index_t col, row;
	int offset;

	if ((_wc_t)wc < 0x80) {
		/* ISO-646 */
		*csid = 0;
		*idx = (_index_t)wc;
	} else if ((_wc_t)wc < 0x100) {
		/* KANA */
		*csid = 1;
		*idx = (_index_t)wc & 0x7F;
	} else {
		/* Kanji (containing Gaiji zone) */
		/*
		 * 94^2 zone (contains a part of Gaiji (0xED40 - 0xEEFC)):
		 * 0x8140 - 0x817E -> 0x2121 - 0x215F
		 * 0x8180 - 0x819E -> 0x2160 - 0x217E
		 * 0x819F - 0x81FC -> 0x2221 - 0x227E
		 *
		 * 0x8240 - 0x827E -> 0x2321 - 0x235F
		 *  ...
		 * 0x9F9F - 0x9FFc -> 0x5E21 - 0x5E7E
		 *
		 * 0xE040 - 0xE07E -> 0x5F21 - 0x5F5F
		 *  ...
		 * 0xEF9F - 0xEFFC -> 0x7E21 - 0x7E7E
		 *
		 * extended Gaiji zone:
		 * 0xF040 - 0xFCFC
		 *
		 * JIS X0213-plane2:
		 * 0xF040 - 0xF09E -> 0x2121 - 0x217E
		 * 0xF140 - 0xF19E -> 0x2321 - 0x237E
		 * ...
		 * 0xF240 - 0xF29E -> 0x2521 - 0x257E
		 *
		 * 0xF09F - 0xF0FC -> 0x2821 - 0x287E
		 * 0xF29F - 0xF2FC -> 0x2C21 - 0x2C7E
		 * ...
		 * 0xF44F - 0xF49E -> 0x2F21 - 0x2F7E
		 *
		 * 0xF49F - 0xF4FC -> 0x6E21 - 0x6E7E
		 * ...
		 * 0xFC9F - 0xFCFC -> 0x7E21 - 0x7E7E
		 */
		row = ((_wc_t)wc >> 8) & 0xFF;
		col = (_wc_t)wc & 0xFF;
		if (!_mskanji1(row) || !_mskanji2(col))
			return (EILSEQ);
		if ((ei->mode & MODE_JIS2004) == 0 || row < 0xF0) {
			*csid = 2;
			offset = 0x81;
		} else {
			*csid = 3;
			if ((_wc_t)wc <= 0xF49E) {
				offset = (_wc_t)wc >= 0xF29F ||
				    ((_wc_t)wc >= 0xF09F &&
				    (_wc_t)wc <= 0xF0FC) ? 0xED : 0xF0;
			} else
				offset = 0xCE;
		}
		row -= offset;
		if (row >= 0x5F)
			row -= 0x40;
		row = row * 2 + 0x21;
		col -= 0x1F;
		if (col >= 0x61)
			col -= 1;
		if (col > 0x7E) {
			row += 1;
			col -= 0x5E;
		}
		*idx = ((_index_t)row << 8) | col;
	}

	return (0);
}