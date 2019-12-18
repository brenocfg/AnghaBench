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
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  XX_FreeSmart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static t_Error
dtsec_im_fm_port_rx_put_buf(t_Handle buffer_pool, uint8_t *buffer,
    t_Handle buf_context)
{

	XX_FreeSmart(buffer);
	return (E_OK);
}