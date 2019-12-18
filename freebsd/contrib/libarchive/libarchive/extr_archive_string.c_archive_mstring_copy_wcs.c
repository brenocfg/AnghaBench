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
struct archive_mstring {int dummy; } ;

/* Variables and functions */
 int archive_mstring_copy_wcs_len (struct archive_mstring*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/  const*) ; 

int
archive_mstring_copy_wcs(struct archive_mstring *aes, const wchar_t *wcs)
{
	return archive_mstring_copy_wcs_len(aes, wcs,
				wcs == NULL ? 0 : wcslen(wcs));
}