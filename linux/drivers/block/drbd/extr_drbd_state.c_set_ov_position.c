#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drbd_device {unsigned long rs_total; unsigned long ov_left; int /*<<< orphan*/  ov_start_sector; int /*<<< orphan*/  ov_position; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;
struct TYPE_4__ {TYPE_1__* connection; } ;
struct TYPE_3__ {int agreed_pro_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BIT_TO_SECT (int) ; 
 unsigned long BM_SECT_TO_BIT (int /*<<< orphan*/ ) ; 
 int C_VERIFY_T ; 
 unsigned long drbd_bm_bits (struct drbd_device*) ; 
 TYPE_2__* first_peer_device (struct drbd_device*) ; 

__attribute__((used)) static void set_ov_position(struct drbd_device *device, enum drbd_conns cs)
{
	if (first_peer_device(device)->connection->agreed_pro_version < 90)
		device->ov_start_sector = 0;
	device->rs_total = drbd_bm_bits(device);
	device->ov_position = 0;
	if (cs == C_VERIFY_T) {
		/* starting online verify from an arbitrary position
		 * does not fit well into the existing protocol.
		 * on C_VERIFY_T, we initialize ov_left and friends
		 * implicitly in receive_DataRequest once the
		 * first P_OV_REQUEST is received */
		device->ov_start_sector = ~(sector_t)0;
	} else {
		unsigned long bit = BM_SECT_TO_BIT(device->ov_start_sector);
		if (bit >= device->rs_total) {
			device->ov_start_sector =
				BM_BIT_TO_SECT(device->rs_total - 1);
			device->rs_total = 1;
		} else
			device->rs_total -= bit;
		device->ov_position = device->ov_start_sector;
	}
	device->ov_left = device->rs_total;
}