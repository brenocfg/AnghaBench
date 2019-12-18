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
struct vio_dring_state {unsigned long entry_size; unsigned long num_entries; unsigned long pending; int ncookies; scalar_t__ cons; scalar_t__ prod; void* base; int /*<<< orphan*/  cookies; } ;
struct vio_disk_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lp; struct vio_dring_state* drings; } ;
struct vdc_port {int ring_cookies; TYPE_1__ vio; } ;
struct ldc_trans_cookie {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int LDC_MAP_DIRECT ; 
 int LDC_MAP_RW ; 
 int LDC_MAP_SHADOW ; 
 int PTR_ERR (void*) ; 
 unsigned long VDC_TX_RING_SIZE ; 
 size_t VIO_DRIVER_TX_RING ; 
 int VIO_MAX_RING_COOKIES ; 
 void* ldc_alloc_exp_dring (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vdc_alloc_tx_ring(struct vdc_port *port)
{
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	unsigned long len, entry_size;
	int ncookies;
	void *dring;

	entry_size = sizeof(struct vio_disk_desc) +
		(sizeof(struct ldc_trans_cookie) * port->ring_cookies);
	len = (VDC_TX_RING_SIZE * entry_size);

	ncookies = VIO_MAX_RING_COOKIES;
	dring = ldc_alloc_exp_dring(port->vio.lp, len,
				    dr->cookies, &ncookies,
				    (LDC_MAP_SHADOW |
				     LDC_MAP_DIRECT |
				     LDC_MAP_RW));
	if (IS_ERR(dring))
		return PTR_ERR(dring);

	dr->base = dring;
	dr->entry_size = entry_size;
	dr->num_entries = VDC_TX_RING_SIZE;
	dr->prod = dr->cons = 0;
	dr->pending = VDC_TX_RING_SIZE;
	dr->ncookies = ncookies;

	return 0;
}