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
 int ETHER_HDR_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int MCLBYTES ; 
 int MJUM9BYTES ; 
 int MJUMPAGESIZE ; 
 int MXGEFW_PAD ; 

__attribute__((used)) static void
mxge_choose_params(int mtu, int *big_buf_size, int *cl_size, int *nbufs)
{
	int bufsize = mtu + ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN + MXGEFW_PAD;

	if (bufsize < MCLBYTES) {
		/* easy, everything fits in a single buffer */
		*big_buf_size = MCLBYTES;
		*cl_size = MCLBYTES;
		*nbufs = 1;
		return;
	}

	if (bufsize < MJUMPAGESIZE) {
		/* still easy, everything still fits in a single buffer */
		*big_buf_size = MJUMPAGESIZE;
		*cl_size = MJUMPAGESIZE;
		*nbufs = 1;
		return;
	}
#if MXGE_VIRT_JUMBOS
	/* now we need to use virtually contiguous buffers */
	*cl_size = MJUM9BYTES;
	*big_buf_size = 4096;
	*nbufs = mtu / 4096 + 1;
	/* needs to be a power of two, so round up */
	if (*nbufs == 3)
		*nbufs = 4;
#else
	*cl_size = MJUM9BYTES;
	*big_buf_size = MJUM9BYTES;
	*nbufs = 1;
#endif
}