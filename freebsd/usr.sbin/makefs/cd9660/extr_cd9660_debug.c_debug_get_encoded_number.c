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
 int isonum_711 (unsigned char*) ; 
 int isonum_712 (char*) ; 
 int isonum_721 (unsigned char*) ; 
 int isonum_722 (unsigned char*) ; 
 int isonum_723 (unsigned char*) ; 
 int isonum_731 (unsigned char*) ; 
 int isonum_732 (unsigned char*) ; 
 int isonum_733 (unsigned char*) ; 

int
debug_get_encoded_number(unsigned char* buf, int mode)
{
#if !HAVE_NBTOOL_CONFIG_H
	switch (mode) {
	/* 711: Single bite */
	case 711:
		return isonum_711(buf);

	/* 712: Single signed byte */
	case 712:
		return isonum_712((signed char *)buf);

	/* 721: 16 bit LE */
	case 721:
		return isonum_721(buf);

	/* 731: 32 bit LE */
	case 731:
		return isonum_731(buf);

	/* 722: 16 bit BE */
	case 722:
		return isonum_722(buf);

	/* 732: 32 bit BE */
	case 732:
		return isonum_732(buf);

	/* 723: 16 bit bothE */
	case 723:
		return isonum_723(buf);

	/* 733: 32 bit bothE */
	case 733:
		return isonum_733(buf);
	}
#endif
	return 0;
}