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
struct archive_mstring {int /*<<< orphan*/  aes_wcs; int /*<<< orphan*/  aes_utf8; int /*<<< orphan*/  aes_mbs; int /*<<< orphan*/  aes_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_wstring_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
archive_mstring_copy(struct archive_mstring *dest, struct archive_mstring *src)
{
	dest->aes_set = src->aes_set;
	archive_string_copy(&(dest->aes_mbs), &(src->aes_mbs));
	archive_string_copy(&(dest->aes_utf8), &(src->aes_utf8));
	archive_wstring_copy(&(dest->aes_wcs), &(src->aes_wcs));
}