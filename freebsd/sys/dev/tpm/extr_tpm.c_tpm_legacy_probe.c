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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int bus_addr_t ;

/* Variables and functions */
 scalar_t__ TPM_ID ; 
 int /*<<< orphan*/  bcmp (char*,char*,int) ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char,char,char,char) ; 
 int /*<<< orphan*/  tpm_enabled ; 
 char tpm_legacy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
tpm_legacy_probe(bus_space_tag_t iot, bus_addr_t iobase)
{
	bus_space_handle_t ioh;
	u_int8_t r, v;
	int i, rv = 0;
	char id[8];

	if (!tpm_enabled || iobase == -1)
		return 0;

	if (bus_space_map(iot, iobase, 2, 0, &ioh))
		return 0;

	v = bus_space_read_1(iot, ioh, 0);
	if (v == 0xff) {
		bus_space_unmap(iot, ioh, 2);
		return 0;
	}
	r = bus_space_read_1(iot, ioh, 1);

	for (i = sizeof(id); i--; )
		id[i] = tpm_legacy_in(iot, ioh, TPM_ID + i);

#ifdef TPM_DEBUG
	printf("tpm_legacy_probe %.4s %d.%d.%d.%d\n",
	    &id[4], id[0], id[1], id[2], id[3]);
#endif
	/*
	 * The only chips using the legacy interface we are aware of are
	 * by Atmel.  For other chips more signature would have to be added.
	 */
	if (!bcmp(&id[4], "ATML", 4))
		rv = 1;

	if (!rv) {
		bus_space_write_1(iot, ioh, r, 1);
		bus_space_write_1(iot, ioh, v, 0);
	}
	bus_space_unmap(iot, ioh, 2);

	return rv;
}