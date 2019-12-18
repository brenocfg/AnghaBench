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
 unsigned char* base64_gen_decode (unsigned char const*,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_table ; 

unsigned char * base64_decode(const unsigned char *src, size_t len,
			      size_t *out_len)
{
	return base64_gen_decode(src, len, out_len, base64_table);
}