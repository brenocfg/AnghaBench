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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  XX_FreeSmart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtsec_im_fm_port_tx_conf_callback(t_Handle app, uint8_t *data, uint16_t status,
    t_Handle buf_context)
{

	/* TODO: Check status */
	XX_FreeSmart(data);
}