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
 int /*<<< orphan*/  CCW_FC_842_DECOMP_CRC ; 
 int nx842_powernv_exec (unsigned char const*,unsigned int,unsigned char*,unsigned int*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nx842_powernv_decompress(const unsigned char *in, unsigned int inlen,
				    unsigned char *out, unsigned int *outlenp,
				    void *wmem)
{
	return nx842_powernv_exec(in, inlen, out, outlenp,
				      wmem, CCW_FC_842_DECOMP_CRC);
}