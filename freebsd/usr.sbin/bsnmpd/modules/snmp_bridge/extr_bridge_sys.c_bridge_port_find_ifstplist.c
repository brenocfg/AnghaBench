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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct ifbpstpreq {scalar_t__ ifbp_portno; } ;

/* Variables and functions */

__attribute__((used)) static struct ifbpstpreq *
bridge_port_find_ifstplist(uint8_t port_no, struct ifbpstpreq *buf,
    uint32_t buf_len)
{
	uint32_t i;
	struct ifbpstpreq *bstp;

	for (i = 0; i < buf_len / sizeof(struct ifbpstpreq); i++) {
		bstp = buf + i;
		if (bstp->ifbp_portno == port_no)
			return (bstp);
	}

	return (NULL);
}