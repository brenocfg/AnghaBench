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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_bps (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ modem ; 
 int /*<<< orphan*/  modem_out_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
modem_write(uint8_t *buf, uint32_t len)
{
	uint32_t n;

	for (n = 0; n != len; n++) {
		modem_out_state(buf + n);
	}

	do_bps("transmitted", &modem.tx_bytes, len);
}