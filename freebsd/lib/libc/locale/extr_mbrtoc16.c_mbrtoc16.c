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
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 size_t mbrtoc16_l (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
mbrtoc16(char16_t * __restrict pc16, const char * __restrict s, size_t n,
    mbstate_t * __restrict ps)
{

	return (mbrtoc16_l(pc16, s, n, ps, __get_locale()));
}