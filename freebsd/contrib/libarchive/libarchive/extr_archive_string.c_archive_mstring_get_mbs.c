#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* s; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;
struct archive_mstring {int aes_set; TYPE_2__ aes_mbs; TYPE_1__ aes_wcs; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int AES_SET_MBS ; 
 int AES_SET_WCS ; 
 int archive_string_append_from_wcs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_2__*) ; 

int
archive_mstring_get_mbs(struct archive *a, struct archive_mstring *aes,
    const char **p)
{
	int r, ret = 0;

	(void)a; /* UNUSED */
	/* If we already have an MBS form, return that immediately. */
	if (aes->aes_set & AES_SET_MBS) {
		*p = aes->aes_mbs.s;
		return (ret);
	}

	*p = NULL;
	/* If there's a WCS form, try converting with the native locale. */
	if (aes->aes_set & AES_SET_WCS) {
		archive_string_empty(&(aes->aes_mbs));
		r = archive_string_append_from_wcs(&(aes->aes_mbs),
		    aes->aes_wcs.s, aes->aes_wcs.length);
		*p = aes->aes_mbs.s;
		if (r == 0) {
			aes->aes_set |= AES_SET_MBS;
			return (ret);
		} else
			ret = -1;
	}

	/*
	 * Only a UTF-8 form cannot avail because its conversion already
	 * failed at archive_mstring_update_utf8().
	 */
	return (ret);
}