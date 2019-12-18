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
typedef  int /*<<< orphan*/  u8 ;
struct bsd_driver_data {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv_event_eapol_rx (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void
handle_read(void *ctx, const u8 *src_addr, const u8 *buf, size_t len)
{
	struct bsd_driver_data *drv = ctx;

	drv_event_eapol_rx(drv->ctx, src_addr, buf, len);
}