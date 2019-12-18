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
typedef  int /*<<< orphan*/  _index_t ;
typedef  int _csid_t ;
struct TYPE_3__ {int mb_cur_max; } ;
typedef  TYPE_1__ _GBK2KEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 

__attribute__((used)) static __inline int
/*ARGSUSED*/
_citrus_GBK2K_stdenc_cstowc(_GBK2KEncodingInfo * __restrict ei,
    wchar_t * __restrict wc, _csid_t csid, _index_t idx)
{

	switch (csid) {
	case 0:
		/* ISO646 */
		*wc = (wchar_t)idx;
		break;
	case 1:
		/* EUC G1 */
		*wc = (wchar_t)idx | 0x8080U;
		break;
	case 2:
		/* extended area */
		*wc = (wchar_t)idx;
		break;
	case 3:
		/* GBKUCS : XXX */
		if (ei->mb_cur_max != 4)
			return (EINVAL);
		*wc = (wchar_t)idx;
		break;
	default:
		return (EILSEQ);
	}

	return (0);
}