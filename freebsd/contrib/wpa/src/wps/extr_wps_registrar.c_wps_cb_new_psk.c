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
struct wps_registrar {int (* new_psk_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  cb_ctx; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int wps_cb_new_psk(struct wps_registrar *reg, const u8 *mac_addr,
		   const u8 *p2p_dev_addr, const u8 *psk, size_t psk_len)
{
	if (reg->new_psk_cb == NULL)
		return 0;

	return reg->new_psk_cb(reg->cb_ctx, mac_addr, p2p_dev_addr, psk,
			       psk_len);
}