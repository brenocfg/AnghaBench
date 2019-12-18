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
struct archive_mstring {int /*<<< orphan*/  aes_wcs; int /*<<< orphan*/  aes_utf8; int /*<<< orphan*/  aes_mbs; scalar_t__ aes_set; } ;

/* Variables and functions */
 scalar_t__ AES_SET_WCS ; 
 int /*<<< orphan*/  archive_string_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_wstrncpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int
archive_mstring_copy_wcs_len(struct archive_mstring *aes, const wchar_t *wcs,
    size_t len)
{
	if (wcs == NULL) {
		aes->aes_set = 0;
		return (0);
	}
	aes->aes_set = AES_SET_WCS; /* Only WCS form set. */
	archive_string_empty(&(aes->aes_mbs));
	archive_string_empty(&(aes->aes_utf8));
	archive_wstrncpy(&(aes->aes_wcs), wcs, len);
	return (0);
}