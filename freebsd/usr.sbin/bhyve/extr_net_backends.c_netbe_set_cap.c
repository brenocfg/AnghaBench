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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct net_backend {unsigned int fe_vnet_hdr_len; int (* set_cap ) (struct net_backend*,int /*<<< orphan*/ ,unsigned int) ;scalar_t__ be_vnet_hdr_len; } ;

/* Variables and functions */
 unsigned int VNET_HDR_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (struct net_backend*,int /*<<< orphan*/ ,unsigned int) ; 

int
netbe_set_cap(struct net_backend *be, uint64_t features,
	      unsigned vnet_hdr_len)
{
	int ret;

	assert(be != NULL);

	/* There are only three valid lengths, i.e., 0, 10 and 12. */
	if (vnet_hdr_len && vnet_hdr_len != VNET_HDR_LEN
		&& vnet_hdr_len != (VNET_HDR_LEN - sizeof(uint16_t)))
		return (-1);

	be->fe_vnet_hdr_len = vnet_hdr_len;

	ret = be->set_cap(be, features, vnet_hdr_len);
	assert(be->be_vnet_hdr_len == 0 ||
	       be->be_vnet_hdr_len == be->fe_vnet_hdr_len);

	return (ret);
}