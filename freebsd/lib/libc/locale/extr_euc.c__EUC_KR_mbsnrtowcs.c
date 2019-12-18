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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  _EUC_KR_mbrtowc ; 
 size_t __mbsnrtowcs_std (int /*<<< orphan*/ *,char const**,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
_EUC_KR_mbsnrtowcs(wchar_t * __restrict dst,
    const char ** __restrict src,
    size_t nms, size_t len, mbstate_t * __restrict ps)
{
	return (__mbsnrtowcs_std(dst, src, nms, len, ps, _EUC_KR_mbrtowc));
}