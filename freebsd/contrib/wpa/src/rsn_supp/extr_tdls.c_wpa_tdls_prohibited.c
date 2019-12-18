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
struct ieee802_11_elems {int* ext_capab; } ;

/* Variables and functions */

__attribute__((used)) static int wpa_tdls_prohibited(struct ieee802_11_elems *elems)
{
	/* bit 38 - TDLS Prohibited */
	return !!(elems->ext_capab[4] & 0x40);
}