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
struct archive_wstring {int dummy; } ;

/* Variables and functions */
 struct archive_wstring* archive_wstrncat (struct archive_wstring*,int /*<<< orphan*/  const*,int) ; 

struct archive_wstring *
archive_wstrcat(struct archive_wstring *as, const wchar_t *p)
{
	/* Ditto. */
	return archive_wstrncat(as, p, 0x1000000);
}