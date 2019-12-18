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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PNP_CONFIG_CONTROL ; 
 int PNP_MAX_CARDS ; 
 int /*<<< orphan*/  PNP_SERIAL_ISOLATION ; 
 int /*<<< orphan*/  PNP_SET_RD_DATA ; 
 int /*<<< orphan*/  PNP_WAKE ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int /*<<< orphan*/  dump_resdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_serial (int /*<<< orphan*/ *) ; 
 scalar_t__ logdevs ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_write (int /*<<< orphan*/ ,int) ; 
 int rd_port ; 
 int /*<<< orphan*/  send_Initiation_LFSR () ; 

int
isolation_protocol()
{
    int csn;
    u_char data[9];

    send_Initiation_LFSR();

    /* Reset CSN for All Cards */
    pnp_write(PNP_CONFIG_CONTROL, 0x04);

    for (csn = 1; (csn < PNP_MAX_CARDS); csn++) {
	/* Wake up cards without a CSN */
	logdevs = 0 ;
	pnp_write(PNP_WAKE, 0);
	pnp_write(PNP_SET_RD_DATA, rd_port);
	outb(_PNP_ADDRESS, PNP_SERIAL_ISOLATION);
	DELAY(1000);	/* Delay 1 msec */

	if (get_serial(data))
	    dump_resdata(data, csn);
	else
	    break;
    }
    return csn - 1;
}