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

/* Variables and functions */
 int towide_dbcs (int /*<<< orphan*/ *,char const*,unsigned int) ; 

int
towide_big5(wchar_t *wc, const char *mb, unsigned n)
{
	return (towide_dbcs(wc, mb, n));
}