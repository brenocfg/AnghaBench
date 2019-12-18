#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  vendor_id; } ;
typedef  TYPE_1__ pnp_id ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PNP_CONFIG_CONTROL ; 
 int PNP_CONFIG_CONTROL_RESET_CSN ; 
 int PNP_CONFIG_CONTROL_WAIT_FOR_KEY ; 
 int PNP_MAX_CARDS ; 
 int /*<<< orphan*/  PNP_SERIAL_ISOLATION ; 
 int /*<<< orphan*/  PNP_SET_CSN ; 
 int /*<<< orphan*/  PNP_SET_RD_DATA ; 
 int /*<<< orphan*/  PNP_WAKE ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_create_devices (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 char* pnp_eisaformat (int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_get_serial (TYPE_1__*) ; 
 int pnp_rd_port ; 
 int pnp_read_resources (int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  pnp_send_initiation_key () ; 
 int /*<<< orphan*/  pnp_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
pnp_isolation_protocol(device_t parent)
{
	int csn;
	pnp_id id;
	int found = 0, len;
	u_char *resources = NULL;
	int space = 0;
	int error;

	/*
	 * Put all cards into the Sleep state so that we can clear
	 * their CSNs.
	 */
	pnp_send_initiation_key();

	/*
	 * Clear the CSN for all cards.
	 */
	pnp_write(PNP_CONFIG_CONTROL, PNP_CONFIG_CONTROL_RESET_CSN);

	/*
	 * Move all cards to the Isolation state.
	 */
	pnp_write(PNP_WAKE, 0);

	/*
	 * Tell them where the read point is going to be this time.
	 */
	pnp_write(PNP_SET_RD_DATA, pnp_rd_port);

	for (csn = 1; csn < PNP_MAX_CARDS; csn++) {
		/*
		 * Start the serial isolation protocol.
		 */
		outb(_PNP_ADDRESS, PNP_SERIAL_ISOLATION);
		DELAY(1000);	/* Delay 1 msec */

		if (pnp_get_serial(&id)) {
			/*
			 * We have read the id from a card
			 * successfully. The card which won the
			 * isolation protocol will be in Isolation
			 * mode and all others will be in Sleep.
			 * Program the CSN of the isolated card
			 * (taking it to Config state) and read its
			 * resources, creating devices as we find
			 * logical devices on the card.
			 */
			pnp_write(PNP_SET_CSN, csn);
			if (bootverbose)
				printf("Reading PnP configuration for %s.\n",
				    pnp_eisaformat(id.vendor_id));
			error = pnp_read_resources(&resources, &space, &len);
			if (error)
				break;
			pnp_create_devices(parent, &id, csn, resources, len);
			found++;
		} else
			break;

		/*
		 * Put this card back to the Sleep state and
		 * simultaneously move all cards which don't have a
		 * CSN yet to Isolation state.
		 */
		pnp_write(PNP_WAKE, 0);
	}

	/*
	 * Unless we have chosen the wrong read port, all cards will
	 * be in Sleep state. Put them back into WaitForKey for
	 * now. Their resources will be programmed later.
	 */
	pnp_write(PNP_CONFIG_CONTROL, PNP_CONFIG_CONTROL_WAIT_FOR_KEY);

	/*
	 * Cleanup.
	 */
	if (resources)
		free(resources, M_TEMP);

	return (found);
}