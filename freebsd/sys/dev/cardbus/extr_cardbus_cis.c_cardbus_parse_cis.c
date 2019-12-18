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
typedef  scalar_t__ uint32_t ;
struct tuple_callbacks {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CISTPL_END ; 
 int CISTPL_LINKTARGET ; 
 int CISTPL_NULL ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MAXTUPLESIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCIR_CIS ; 
 int TRUE ; 
 scalar_t__ cardbus_read_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,scalar_t__,scalar_t__*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cardbus_read_tuple_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 struct resource* cardbus_read_tuple_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int decode_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,struct tuple_callbacks*,void*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
cardbus_parse_cis(device_t cbdev, device_t child,
    struct tuple_callbacks *callbacks, void *argp)
{
	uint8_t *tupledata;
	int tupleid = CISTPL_NULL;
	int len;
	int expect_linktarget;
	uint32_t start, off;
	struct resource *res;
	int rid;

	tupledata = malloc(MAXTUPLESIZE, M_DEVBUF, M_WAITOK | M_ZERO);
	expect_linktarget = TRUE;
	if ((start = pci_read_config(child, PCIR_CIS, 4)) == 0) {
		DEVPRINTF((cbdev, "Warning: CIS pointer is 0: (no CIS)\n"));
		free(tupledata, M_DEVBUF);
		return (0);
	}
	DEVPRINTF((cbdev, "CIS pointer is %#x\n", start));
	off = 0;
	res = cardbus_read_tuple_init(cbdev, child, &start, &rid);
	if (res == NULL) {
		device_printf(cbdev, "Unable to allocate resources for CIS\n");
		free(tupledata, M_DEVBUF);
		return (ENXIO);
	}

	do {
		if (cardbus_read_tuple(cbdev, child, res, start, &off,
		    &tupleid, &len, tupledata) != 0) {
			device_printf(cbdev, "Failed to read CIS.\n");
			cardbus_read_tuple_finish(cbdev, child, rid, res);
			free(tupledata, M_DEVBUF);
			return (ENXIO);
		}

		if (expect_linktarget && tupleid != CISTPL_LINKTARGET) {
			device_printf(cbdev, "Expecting link target, got 0x%x\n",
			    tupleid);
			cardbus_read_tuple_finish(cbdev, child, rid, res);
			free(tupledata, M_DEVBUF);
			return (EINVAL);
		}
		expect_linktarget = decode_tuple(cbdev, child, tupleid, len,
		    tupledata, start, &off, callbacks, argp);
		if (expect_linktarget != 0) {
			device_printf(cbdev, "Parsing failed with %d\n",
			    expect_linktarget);
			cardbus_read_tuple_finish(cbdev, child, rid, res);
			free(tupledata, M_DEVBUF);
			return (expect_linktarget);
		}
	} while (tupleid != CISTPL_END);
	cardbus_read_tuple_finish(cbdev, child, rid, res);
	free(tupledata, M_DEVBUF);
	return (0);
}