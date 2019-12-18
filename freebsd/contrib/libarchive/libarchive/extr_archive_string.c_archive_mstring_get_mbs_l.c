#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct archive_string_conv {int dummy; } ;
struct TYPE_7__ {char* s; size_t length; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;
struct archive_mstring {int aes_set; TYPE_2__ aes_mbs_in_locale; TYPE_2__ aes_mbs; TYPE_1__ aes_wcs; } ;

/* Variables and functions */
 int AES_SET_MBS ; 
 int AES_SET_WCS ; 
 scalar_t__ ENOMEM ; 
 int archive_string_append_from_wcs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int archive_string_append_from_wcs_in_codepage (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct archive_string_conv*) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_2__*) ; 
 int archive_strncpy_l (TYPE_2__*,char*,size_t,struct archive_string_conv*) ; 
 scalar_t__ errno ; 

int
archive_mstring_get_mbs_l(struct archive_mstring *aes,
    const char **p, size_t *length, struct archive_string_conv *sc)
{
	int r, ret = 0;

#if defined(_WIN32) && !defined(__CYGWIN__)
	/*
	 * Internationalization programming on Windows must use Wide
	 * characters because Windows platform cannot make locale UTF-8.
	 */
	if (sc != NULL && (aes->aes_set & AES_SET_WCS) != 0) {
		archive_string_empty(&(aes->aes_mbs_in_locale));
		r = archive_string_append_from_wcs_in_codepage(
		    &(aes->aes_mbs_in_locale), aes->aes_wcs.s,
		    aes->aes_wcs.length, sc);
		if (r == 0) {
			*p = aes->aes_mbs_in_locale.s;
			if (length != NULL)
				*length = aes->aes_mbs_in_locale.length;
			return (0);
		} else if (errno == ENOMEM)
			return (-1);
		else
			ret = -1;
	}
#endif

	/* If there is not an MBS form but is a WCS form, try converting
	 * with the native locale to be used for translating it to specified
	 * character-set. */
	if ((aes->aes_set & AES_SET_MBS) == 0 &&
	    (aes->aes_set & AES_SET_WCS) != 0) {
		archive_string_empty(&(aes->aes_mbs));
		r = archive_string_append_from_wcs(&(aes->aes_mbs),
		    aes->aes_wcs.s, aes->aes_wcs.length);
		if (r == 0)
			aes->aes_set |= AES_SET_MBS;
		else if (errno == ENOMEM)
			return (-1);
		else
			ret = -1;
	}
	/* If we already have an MBS form, use it to be translated to
	 * specified character-set. */
	if (aes->aes_set & AES_SET_MBS) {
		if (sc == NULL) {
			/* Conversion is unneeded. */
			*p = aes->aes_mbs.s;
			if (length != NULL)
				*length = aes->aes_mbs.length;
			return (0);
		}
		ret = archive_strncpy_l(&(aes->aes_mbs_in_locale),
		    aes->aes_mbs.s, aes->aes_mbs.length, sc);
		*p = aes->aes_mbs_in_locale.s;
		if (length != NULL)
			*length = aes->aes_mbs_in_locale.length;
	} else {
		*p = NULL;
		if (length != NULL)
			*length = 0;
	}
	return (ret);
}