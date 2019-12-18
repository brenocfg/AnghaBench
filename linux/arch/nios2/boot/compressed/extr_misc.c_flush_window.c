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
typedef  int ulg ;
typedef  int uch ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_out ; 
 int crc ; 
 int* crc_32_tab ; 
 unsigned int outcnt ; 
 int* output_data ; 
 size_t output_ptr ; 
 int* window ; 

__attribute__((used)) static void flush_window(void)
{
	ulg c = crc;	/* temporary variable */
	unsigned n;
	uch *in, *out, ch;

	in = window;
	out = &output_data[output_ptr];
	for (n = 0; n < outcnt; n++) {
		ch = *out++ = *in++;
		c = crc_32_tab[((int)c ^ ch) & 0xff] ^ (c >> 8);
	}
	crc = c;
	bytes_out += (ulg)outcnt;
	output_ptr += (ulg)outcnt;
	outcnt = 0;
}