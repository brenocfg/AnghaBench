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
typedef  int wchar_t ;
typedef  int uint32_t ;
typedef  int _index_t ;
typedef  int _csid_t ;
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ _MSKanjiEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int MODE_JIS2004 ; 

__attribute__((used)) static __inline int
/*ARGSUSED*/
_citrus_MSKanji_stdenc_cstowc(_MSKanjiEncodingInfo * __restrict ei,
    wchar_t * __restrict wc, _csid_t csid, _index_t idx)
{
	uint32_t col, row;
	int offset;

	switch (csid) {
	case 0:
		/* ISO-646 */
		if (idx >= 0x80)
			return (EILSEQ);
		*wc = (wchar_t)idx;
		break;
	case 1:
		/* kana */
		if (idx >= 0x80)
			return (EILSEQ);
		*wc = (wchar_t)idx + 0x80;
		break;
	case 3:
		if ((ei->mode & MODE_JIS2004) == 0)
			return (EILSEQ);
	/*FALLTHROUGH*/
	case 2:
		/* kanji */
		row = (idx >> 8);
		if (row < 0x21)
			return (EILSEQ);
		if (csid == 3) {
			if (row <= 0x2F)
				offset = (row == 0x22 || row >= 0x26) ?
				    0xED : 0xF0;
			else if (row >= 0x4D && row <= 0x7E)
				offset = 0xCE;
			else
				return (EILSEQ);
		} else {
			if (row > 0x97)
				return (EILSEQ);
			offset = (row < 0x5F) ? 0x81 : 0xC1;
		}
		col = idx & 0xFF;
		if (col < 0x21 || col > 0x7E)
			return (EILSEQ);
		row -= 0x21; col -= 0x21;
		if ((row & 1) == 0) {
			col += 0x40;
			if (col >= 0x7F)
				col += 1;
		} else
			col += 0x9F;
		row = row / 2 + offset;
		*wc = ((wchar_t)row << 8) | col;
		break;
	default:
		return (EILSEQ);
	}

	return (0);
}