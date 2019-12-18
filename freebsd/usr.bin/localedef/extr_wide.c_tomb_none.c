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
typedef  int wchar_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int mb_cur_max ; 
 int /*<<< orphan*/  werr (char*) ; 

int
tomb_none(char *mb, wchar_t wc)
{
	if (mb_cur_max != 1) {
		werr("invalid or unsupported multibyte locale");
		return (-1);
	}
	*(uint8_t *)mb = (wc & 0xff);
	mb[1] = 0;
	return (1);
}