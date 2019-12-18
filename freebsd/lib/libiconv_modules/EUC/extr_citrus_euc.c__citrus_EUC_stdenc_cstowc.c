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
typedef  int _index_t ;
typedef  int _csid_t ;
struct TYPE_3__ {int mask; } ;
typedef  TYPE_1__ _EUCEncodingInfo ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static __inline int
/*ARGSUSED*/
_citrus_EUC_stdenc_cstowc(_EUCEncodingInfo * __restrict ei,
    wchar_t * __restrict wc, _csid_t csid, _index_t idx)
{

	if ((csid & ~ei->mask) != 0 || (idx & ei->mask) != 0)
		return (EINVAL);

	*wc = (wchar_t)csid | (wchar_t)idx;

	return (0);
}