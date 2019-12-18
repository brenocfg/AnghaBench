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
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct vio_ver_info {int /*<<< orphan*/  tag; int /*<<< orphan*/  dev_class; void* minor; void* major; } ;
struct vio_driver_state {int /*<<< orphan*/  dev_class; scalar_t__ _local_sid; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  VIO_VER_INFO ; 
 int /*<<< orphan*/  init_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vio_ver_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sched_clock () ; 
 int send_ctrl (struct vio_driver_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_version(struct vio_driver_state *vio, u16 major, u16 minor)
{
	struct vio_ver_info pkt;

	vio->_local_sid = (u32) sched_clock();

	memset(&pkt, 0, sizeof(pkt));
	init_tag(&pkt.tag, VIO_TYPE_CTRL, VIO_SUBTYPE_INFO, VIO_VER_INFO);
	pkt.major = major;
	pkt.minor = minor;
	pkt.dev_class = vio->dev_class;

	viodbg(HS, "SEND VERSION INFO maj[%u] min[%u] devclass[%u]\n",
	       major, minor, vio->dev_class);

	return send_ctrl(vio, &pkt.tag, sizeof(pkt));
}