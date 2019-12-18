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

/* Variables and functions */
 int OPENPGP_TAG_ISNEW ; 
 int OPENPGP_TAG_ISTAG ; 
 int OPENPGP_TAG_NEW_MASK ; 
 int OPENPGP_TAG_OLD_MASK ; 
 int OPENPGP_TAG_OLD_TYPE ; 

int
decode_tag(unsigned char *ptr, int *isnew, int *ltype)
{
	int tag;

	if (!ptr || !isnew || !ltype)
		return (-1);
	tag = *ptr;

	if (!(tag & OPENPGP_TAG_ISTAG))
		return (-1);		/* we are lost! */
	*isnew = tag & OPENPGP_TAG_ISNEW;
	if (*isnew) {
		*ltype = -1;		/* irrelevant */
		tag &= OPENPGP_TAG_NEW_MASK;
	} else {
		*ltype = tag & OPENPGP_TAG_OLD_TYPE;
		tag = (tag & OPENPGP_TAG_OLD_MASK) >> 2;
	}
	return (tag);
}