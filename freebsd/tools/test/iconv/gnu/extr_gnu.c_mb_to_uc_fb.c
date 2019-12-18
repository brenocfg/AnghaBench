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
 int mb_uc_fb ; 

void
mb_to_uc_fb(const char* inbuf, size_t inbufsize,
    void (*write_replacement)(const unsigned int *buf, size_t buflen,
       void* callback_arg), void* callback_arg, void* data)
{
	unsigned int c = 0x3F;

	mb_uc_fb = true;
	write_replacement((const unsigned int *)&c, 1, NULL);
}