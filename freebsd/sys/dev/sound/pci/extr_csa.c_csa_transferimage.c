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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csa_transferimage(csa_res *resp, u_int32_t *src, u_long dest, u_long len)
{
	u_long ul;
	
	/*
	 * We do not allow DMAs from host memory to host memory (although the DMA
	 * can do it) and we do not allow DMAs which are not a multiple of 4 bytes
	 * in size (because that DMA can not do that).  Return an error if either
	 * of these conditions exist.
	 */
	if ((len & 0x3) != 0)
		return (EINVAL);

	/* Check the destination address that it is a multiple of 4 */
	if ((dest & 0x3) != 0)
		return (EINVAL);

	/* Write the buffer out. */
	for (ul = 0 ; ul < len ; ul += 4)
		csa_writemem(resp, dest + ul, src[ul >> 2]);
	return (0);
}