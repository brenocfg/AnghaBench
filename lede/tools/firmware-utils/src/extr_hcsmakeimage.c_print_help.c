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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_help ( const char* ename )
{
	printf ( "Firmware image packer and calculator for broadcom-based modems.\n" );
	printf ( "Part of bcm-utils package.\n" );
	printf ( "(c) 2009 Necromant (http://necromant.ath.cx). Thanks to Luke-jr for his initial work.\n" );
	printf ( "usage: %s [options]\n", ename );
	printf ( "Valid options are:\n" );
	printf ( "--magic_bytes=value \t- specify magic bytes at the beginning of the image. default - 3349\n" );
	printf ( "\t\t\t these can be sa2100 (for DPC2100 modem),\n\t\t\t sa3349 (haxorware guys use this one for some reason),\n\t\t\t or a custom hex value e.g. 0xFFFF\n" );
	printf ( "--compress \t\t - Make use of LZMA (weird!) compression (Doesn't work yet).\n" );
	printf ( "--rev_maj=value\t\t - major revision number. default 0\n" );
	printf ( "--rev_min=value\t\t - minor revision number default 0\n" );
	printf ( "--filename=value\t - use this filename in header instead of default (input filename)\n" );
	printf ( "--ldaddress=value\t - hex value of the target load address. defaults to 0x80010000\n" );
	printf ( "--input_file=value\t - What file are we packing?\n" );
	printf ( "--output_file=value\t - What file shall we write? (default: image.bin)\n" );
#ifdef _HAX0RSTYLE
	printf ( "--credz\t - Give some credz!\n" );
#endif
	printf ( "\n" );
}