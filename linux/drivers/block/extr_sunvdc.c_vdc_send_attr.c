#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vio_driver_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
struct vio_disk_attr_info {int /*<<< orphan*/  max_xfer_size; int /*<<< orphan*/  vdisk_block_size; int /*<<< orphan*/  xfer_mode; TYPE_1__ tag; } ;
struct vdc_port {int /*<<< orphan*/  vio; int /*<<< orphan*/  max_xfer_size; int /*<<< orphan*/  vdisk_block_size; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_ATTR_INFO ; 
 int /*<<< orphan*/  VIO_DRING_MODE ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  memset (struct vio_disk_attr_info*,int /*<<< orphan*/ ,int) ; 
 struct vdc_port* to_vdc_port (struct vio_driver_state*) ; 
 int vio_ldc_send (int /*<<< orphan*/ *,struct vio_disk_attr_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdc_send_attr(struct vio_driver_state *vio)
{
	struct vdc_port *port = to_vdc_port(vio);
	struct vio_disk_attr_info pkt;

	memset(&pkt, 0, sizeof(pkt));

	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.stype = VIO_SUBTYPE_INFO;
	pkt.tag.stype_env = VIO_ATTR_INFO;
	pkt.tag.sid = vio_send_sid(vio);

	pkt.xfer_mode = VIO_DRING_MODE;
	pkt.vdisk_block_size = port->vdisk_block_size;
	pkt.max_xfer_size = port->max_xfer_size;

	viodbg(HS, "SEND ATTR xfer_mode[0x%x] blksz[%u] max_xfer[%llu]\n",
	       pkt.xfer_mode, pkt.vdisk_block_size, pkt.max_xfer_size);

	return vio_ldc_send(&port->vio, &pkt, sizeof(pkt));
}