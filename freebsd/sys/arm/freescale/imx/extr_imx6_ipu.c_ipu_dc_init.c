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
typedef  int uint32_t ;
struct ipu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_EVENT_EOF ; 
 int /*<<< orphan*/  DC_EVENT_EOFIELD ; 
 int /*<<< orphan*/  DC_EVENT_EOL ; 
 int /*<<< orphan*/  DC_EVENT_NEW_ADDR ; 
 int /*<<< orphan*/  DC_EVENT_NEW_CHAN ; 
 int /*<<< orphan*/  DC_EVENT_NEW_DATA ; 
 int /*<<< orphan*/  DC_EVENT_NF ; 
 int /*<<< orphan*/  DC_EVENT_NFIELD ; 
 int /*<<< orphan*/  DC_EVENT_NL ; 
 int /*<<< orphan*/  DC_GEN ; 
 int DC_GEN_SYNC ; 
 int DC_GEN_SYNC_PRIORITY ; 
 int /*<<< orphan*/  DC_WRITE_CH_ADDR_5 ; 
 int /*<<< orphan*/  DC_WRITE_CH_CONF_5 ; 
 int /*<<< orphan*/  DI_PORT ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int /*<<< orphan*/ ,int) ; 
 int WRITE_CH_CONF_PROG_DISP_ID (int /*<<< orphan*/ ) ; 
 int WRITE_CH_CONF_PROG_DI_ID (int /*<<< orphan*/ ) ; 
 int WRITE_CH_CONF_PROG_W_SIZE (int) ; 
 int /*<<< orphan*/  ipu_dc_link_event (struct ipu_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ipu_dc_init(struct ipu_softc *sc, int di_port)
{
	int addr;
	uint32_t conf;

	if (di_port)
		addr = 2;
	else
		addr = 5;

	ipu_dc_link_event(sc, DC_EVENT_NL, addr, 3);
	ipu_dc_link_event(sc, DC_EVENT_EOL, addr + 1, 2);
	ipu_dc_link_event(sc, DC_EVENT_NEW_DATA, addr + 2, 1);
	ipu_dc_link_event(sc, DC_EVENT_NF, 0, 0);
	ipu_dc_link_event(sc, DC_EVENT_NFIELD, 0, 0);
	ipu_dc_link_event(sc, DC_EVENT_EOF, 0, 0);
	ipu_dc_link_event(sc, DC_EVENT_EOFIELD, 0, 0);
	ipu_dc_link_event(sc, DC_EVENT_NEW_CHAN, 0, 0);
	ipu_dc_link_event(sc, DC_EVENT_NEW_ADDR, 0, 0);

	conf = WRITE_CH_CONF_PROG_W_SIZE(0x02) |
            WRITE_CH_CONF_PROG_DISP_ID(DI_PORT) |
	    WRITE_CH_CONF_PROG_DI_ID(DI_PORT);

	IPU_WRITE4(sc, DC_WRITE_CH_CONF_5, conf);
	IPU_WRITE4(sc, DC_WRITE_CH_ADDR_5, 0x00000000);
	IPU_WRITE4(sc, DC_GEN, DC_GEN_SYNC_PRIORITY | DC_GEN_SYNC); /* High priority, sync */
}