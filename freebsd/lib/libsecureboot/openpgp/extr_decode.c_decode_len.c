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
 int decode_new_len (unsigned char**) ; 

__attribute__((used)) static int
decode_len(unsigned char **pptr, int ltype)
{
	unsigned char *ptr;
	int len;

	if (ltype < 0)
		return (decode_new_len(pptr));

	if (pptr == NULL)
		return (-1);

	ptr = *pptr;

	switch (ltype) {
	case 0:
		len = *ptr++;
		break;
	case 1:
		len = (*ptr++ << 8);
		len |= *ptr++;
		break;
	case 2:
		len =  *ptr++ << 24;
		len |= *ptr++ << 16;
		len |= *ptr++ << 8;
		len |= *ptr++;
		break;
	case 3:
	default:
		/* Not supported */
		len = -1;
	}

	*pptr = ptr;
	return (len);
}