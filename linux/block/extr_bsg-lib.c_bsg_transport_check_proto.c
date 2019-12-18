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
struct sg_io_v4 {scalar_t__ protocol; scalar_t__ subprotocol; } ;

/* Variables and functions */
 scalar_t__ BSG_PROTOCOL_SCSI ; 
 scalar_t__ BSG_SUB_PROTOCOL_SCSI_TRANSPORT ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bsg_transport_check_proto(struct sg_io_v4 *hdr)
{
	if (hdr->protocol != BSG_PROTOCOL_SCSI  ||
	    hdr->subprotocol != BSG_SUB_PROTOCOL_SCSI_TRANSPORT)
		return -EINVAL;
	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;
	return 0;
}