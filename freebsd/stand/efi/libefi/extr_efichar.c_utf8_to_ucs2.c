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
typedef  int uint32_t ;
typedef  scalar_t__ efi_char ;

/* Variables and functions */
 int EDOOFUS ; 
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (size_t) ; 
 int strlen (char const*) ; 

int
utf8_to_ucs2(const char *name, efi_char **nmp, size_t *len)
{
	efi_char *nm;
	size_t sz;
	uint32_t ucs4;
	int c, bytes;
	int freeit = *nmp == NULL;

	sz = strlen(name) * 2 + 2;
	if (*nmp == NULL)
		*nmp = malloc(sz);
	if (*nmp == NULL)
		return (ENOMEM);
	nm = *nmp;
	*len = sz;

	ucs4 = 0;
	bytes = 0;
	while (sz > 1 && *name != '\0') {
		c = *name++;
		/*
		 * Conditionalize on the two major character types:
		 * initial and followup characters.
		 */
		if ((c & 0xc0) != 0x80) {
			/* Initial characters. */
			if (bytes != 0)
				goto ilseq;
			if ((c & 0xf8) == 0xf0) {
				ucs4 = c & 0x07;
				bytes = 3;
			} else if ((c & 0xf0) == 0xe0) {
				ucs4 = c & 0x0f;
				bytes = 2;
			} else if ((c & 0xe0) == 0xc0) {
				ucs4 = c & 0x1f;
				bytes = 1;
			} else {
				ucs4 = c & 0x7f;
				bytes = 0;
			}
		} else {
			/* Followup characters. */
			if (bytes > 0) {
				ucs4 = (ucs4 << 6) + (c & 0x3f);
				bytes--;
			} else if (bytes == 0)
				goto ilseq;
		}
		if (bytes == 0) {
			if (ucs4 > 0xffff)
				goto ilseq;
			*nm++ = (efi_char)ucs4;
			sz -= 2;
		}
	}
	if (sz < 2) {
		if (freeit) {
			free(nm);
			*nmp = NULL;
		}
		return (EDOOFUS);
	}
	sz -= 2;
	*nm = 0;
	*len -= sz;
	return (0);
ilseq:
	if (freeit) {
		free(nm);
		*nmp = NULL;
	}
	return (EILSEQ);
}