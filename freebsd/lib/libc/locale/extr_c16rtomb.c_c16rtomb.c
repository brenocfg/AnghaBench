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
 size_t c16rtomb_l (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
c16rtomb(char * __restrict s, char16_t c16, mbstate_t * __restrict ps)
{

	return (c16rtomb_l(s, c16, ps, __get_locale()));
}