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

int jvp_utf8_decode_length(char startchar) {
	if ((startchar & 0x80) == 0) return 1;         // 0___ ____
	else if ((startchar & 0xE0) == 0xC0) return 2; // 110_ ____
	else if ((startchar & 0xF0) == 0xE0) return 3; // 1110 ____
	else return 4;                                 // 1111 ____
}