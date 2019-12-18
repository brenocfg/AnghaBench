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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __svfscanf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
vfscanf_l(FILE *fp, locale_t locale, char const *fmt0, va_list ap)
{
	int ret;
	FIX_LOCALE(locale);

	FLOCKFILE_CANCELSAFE(fp);
	ret = __svfscanf(fp, locale, fmt0, ap);
	FUNLOCKFILE_CANCELSAFE();
	return (ret);
}