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
 int /*<<< orphan*/  SS2 ; 
 size_t _EUC_mbrtowc_impl (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
_EUC_TW_mbrtowc(wchar_t * __restrict pwc, const char * __restrict s,
	size_t n, mbstate_t * __restrict ps)
{
	return (_EUC_mbrtowc_impl(pwc, s, n, ps, SS2, 4, 0, 0));
}