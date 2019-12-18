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
struct archive_mstring {int /*<<< orphan*/  aes_utf8; int /*<<< orphan*/  aes_wcs; int /*<<< orphan*/  aes_mbs; scalar_t__ aes_set; } ;

/* Variables and functions */
 scalar_t__ AES_SET_UTF8 ; 
 int /*<<< orphan*/  archive_string_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_strncpy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int
archive_mstring_copy_utf8(struct archive_mstring *aes, const char *utf8)
{
  if (utf8 == NULL) {
    aes->aes_set = 0;
    return (0);
  }
  aes->aes_set = AES_SET_UTF8;
  archive_string_empty(&(aes->aes_mbs));
  archive_string_empty(&(aes->aes_wcs));
  archive_strncpy(&(aes->aes_utf8), utf8, strlen(utf8));
  return (int)strlen(utf8);
}