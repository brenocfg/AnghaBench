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
struct vio_driver_state {int dr_state; int /*<<< orphan*/  hs_state; scalar_t__ desc_buf_len; int /*<<< orphan*/ * desc_buf; struct vio_dring_state* drings; } ;
struct vio_dring_state {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  HS ; 
 size_t VIO_DRIVER_RX_RING ; 
 int VIO_DR_STATE_RXREG ; 
 int VIO_DR_STATE_TXREG ; 
 int /*<<< orphan*/  VIO_HS_INVALID ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vio_dring_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int handshake_failure(struct vio_driver_state *vio)
{
	struct vio_dring_state *dr;

	/* XXX Put policy here...  Perhaps start a timer to fire
	 * XXX in 100 ms, which will bring the link up and retry
	 * XXX the handshake.
	 */

	viodbg(HS, "HANDSHAKE FAILURE\n");

	vio->dr_state &= ~(VIO_DR_STATE_TXREG |
			   VIO_DR_STATE_RXREG);

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	memset(dr, 0, sizeof(*dr));

	kfree(vio->desc_buf);
	vio->desc_buf = NULL;
	vio->desc_buf_len = 0;

	vio->hs_state = VIO_HS_INVALID;

	return -ECONNRESET;
}