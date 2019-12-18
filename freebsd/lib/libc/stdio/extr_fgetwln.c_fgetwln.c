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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/ * fgetwln_l (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

wchar_t *
fgetwln(FILE * __restrict fp, size_t *lenp)
{
	return fgetwln_l(fp, lenp, __get_locale());
}