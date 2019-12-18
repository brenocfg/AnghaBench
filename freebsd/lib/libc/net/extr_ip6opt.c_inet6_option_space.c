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
 int CMSG_SPACE (int) ; 

int
inet6_option_space(int nbytes)
{
	nbytes += 2;	/* we need space for nxt-hdr and length fields */
	return(CMSG_SPACE((nbytes + 7) & ~7));
}