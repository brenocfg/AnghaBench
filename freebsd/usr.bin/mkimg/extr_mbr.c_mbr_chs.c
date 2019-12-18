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
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  mkimg_chs (int /*<<< orphan*/ ,int,int*,int*,int*) ; 

__attribute__((used)) static void
mbr_chs(u_char *cylp, u_char *hdp, u_char *secp, lba_t lba)
{
	u_int cyl, hd, sec;

	mkimg_chs(lba, 1023, &cyl, &hd, &sec);
	*cylp = cyl;
	*hdp = hd;
	*secp = (sec & 0x3f) | ((cyl >> 2) & 0xc0);
}