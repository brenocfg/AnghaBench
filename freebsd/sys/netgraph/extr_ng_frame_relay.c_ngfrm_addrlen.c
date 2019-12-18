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
 char BYTEX_EA ; 

int
ngfrm_addrlen(char *hdr)
{
	if (hdr[0] & BYTEX_EA)
		return 0;
	if (hdr[1] & BYTEX_EA)
		return 2;
	if (hdr[2] & BYTEX_EA)
		return 3;
	if (hdr[3] & BYTEX_EA)
		return 4;
	return 0;
}