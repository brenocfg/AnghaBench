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
typedef  int uintmax_t ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static uintmax_t
mmcsd_pretty_size(off_t size, char *unit)
{
	uintmax_t bytes;
	int i;

	/*
	 * Display in most natural units.  There's no card < 1MB.  However,
	 * RPMB partitions occasionally are smaller than that, though.  The
	 * SD standard goes to 2 GiB due to its reliance on FAT, but the data
	 * format supports up to 4 GiB and some card makers push it up to this
	 * limit.  The SDHC standard only goes to 32 GiB due to FAT32, but the
	 * data format supports up to 2 TiB however.  2048 GB isn't too ugly,
	 * so we note it in passing here and don't add the code to print TB).
	 * Since these cards are sold in terms of MB and GB not MiB and GiB,
	 * report them like that.  We also round to the nearest unit, since
	 * many cards are a few percent short, even of the power of 10 size.
	 */
	bytes = size;
	unit[0] = unit[1] = '\0';
	for (i = 0; i <= 2 && bytes >= 1000; i++) {
		bytes = (bytes + 1000 / 2 - 1) / 1000;
		switch (i) {
		case 0:
			unit[0] = 'k';
			break;
		case 1:
			unit[0] = 'M';
			break;
		case 2:
			unit[0] = 'G';
			break;
		default:
			break;
		}
	}
	return (bytes);
}