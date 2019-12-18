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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {int /*<<< orphan*/ * s; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;
struct archive_mstring {int aes_set; TYPE_2__ aes_wcs; TYPE_1__ aes_mbs; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int AES_SET_MBS ; 
 int AES_SET_WCS ; 
 int archive_wstring_append_from_mbs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_wstring_empty (TYPE_2__*) ; 

int
archive_mstring_get_wcs(struct archive *a, struct archive_mstring *aes,
    const wchar_t **wp)
{
	int r, ret = 0;

	(void)a;/* UNUSED */
	/* Return WCS form if we already have it. */
	if (aes->aes_set & AES_SET_WCS) {
		*wp = aes->aes_wcs.s;
		return (ret);
	}

	*wp = NULL;
	/* Try converting MBS to WCS using native locale. */
	if (aes->aes_set & AES_SET_MBS) {
		archive_wstring_empty(&(aes->aes_wcs));
		r = archive_wstring_append_from_mbs(&(aes->aes_wcs),
		    aes->aes_mbs.s, aes->aes_mbs.length);
		if (r == 0) {
			aes->aes_set |= AES_SET_WCS;
			*wp = aes->aes_wcs.s;
		} else
			ret = -1;/* failure. */
	}
	return (ret);
}