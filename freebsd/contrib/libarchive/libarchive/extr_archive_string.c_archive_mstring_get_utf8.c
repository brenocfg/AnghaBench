#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct archive_string_conv {int dummy; } ;
struct TYPE_4__ {char* s; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;
struct archive_mstring {int aes_set; TYPE_2__ aes_utf8; TYPE_1__ aes_mbs; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int AES_SET_MBS ; 
 int AES_SET_UTF8 ; 
 struct archive_string_conv* archive_string_conversion_to_charset (struct archive*,char*,int) ; 
 int archive_strncpy_l (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  free_sconv_object (struct archive_string_conv*) ; 

int
archive_mstring_get_utf8(struct archive *a, struct archive_mstring *aes,
  const char **p)
{
	struct archive_string_conv *sc;
	int r;

	/* If we already have a UTF8 form, return that immediately. */
	if (aes->aes_set & AES_SET_UTF8) {
		*p = aes->aes_utf8.s;
		return (0);
	}

	*p = NULL;
	if (aes->aes_set & AES_SET_MBS) {
		sc = archive_string_conversion_to_charset(a, "UTF-8", 1);
		if (sc == NULL)
			return (-1);/* Couldn't allocate memory for sc. */
		r = archive_strncpy_l(&(aes->aes_utf8), aes->aes_mbs.s,
		    aes->aes_mbs.length, sc);
		if (a == NULL)
			free_sconv_object(sc);
		if (r == 0) {
			aes->aes_set |= AES_SET_UTF8;
			*p = aes->aes_utf8.s;
			return (0);/* success. */
		} else
			return (-1);/* failure. */
	}
	return (0);/* success. */
}