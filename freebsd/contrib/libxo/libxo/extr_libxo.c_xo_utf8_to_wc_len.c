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
typedef  int uint8_t ;
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static inline ssize_t
xo_utf8_to_wc_len (const char *buf)
{
    uint8_t bval = (uint8_t) *buf;
    ssize_t len;

    if ((bval & 0x80) == 0x0)
	len = 1;
    else if ((bval & 0xe0) == 0xc0)
	len = 2;
    else if ((bval & 0xf0) == 0xe0)
	len = 3;
    else if ((bval & 0xf8) == 0xf0)
	len = 4;
    else
	len = -1;

    return len;
}