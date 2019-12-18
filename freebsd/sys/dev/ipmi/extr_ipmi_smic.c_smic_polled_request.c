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
typedef  scalar_t__ u_char ;
struct ipmi_softc {int /*<<< orphan*/  ipmi_dev; } ;
struct ipmi_request {int ir_requestlen; scalar_t__ ir_command; scalar_t__ ir_compcode; int ir_replybuflen; int ir_replylen; scalar_t__* ir_reply; int /*<<< orphan*/  ir_addr; scalar_t__* ir_request; } ;

/* Variables and functions */
 scalar_t__ IPMI_REPLY_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int smic_read_byte (struct ipmi_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  smic_read_end (struct ipmi_softc*) ; 
 int smic_start_read (struct ipmi_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  smic_start_write (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smic_write_last (struct ipmi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  smic_write_next (struct ipmi_softc*,scalar_t__) ; 

__attribute__((used)) static int
smic_polled_request(struct ipmi_softc *sc, struct ipmi_request *req)
{
	u_char *cp, data;
	int i, state;

	/* First, start the message with the address. */
	if (!smic_start_write(sc, req->ir_addr))
		return (0);
#ifdef SMIC_DEBUG
	device_printf(sc->ipmi_dev, "SMIC: WRITE_START address: %02x\n",
	    req->ir_addr);
#endif

	if (req->ir_requestlen == 0) {
		/* Send the command as the last byte. */
		if (!smic_write_last(sc, req->ir_command))
			return (0);
#ifdef SMIC_DEBUG
		device_printf(sc->ipmi_dev, "SMIC: Wrote command: %02x\n",
		    req->ir_command);
#endif
	} else {
		/* Send the command. */
		if (!smic_write_next(sc, req->ir_command))
			return (0);
#ifdef SMIC_DEBUG
		device_printf(sc->ipmi_dev, "SMIC: Wrote command: %02x\n",
		    req->ir_command);
#endif

		/* Send the payload. */
		cp = req->ir_request;
		for (i = 0; i < req->ir_requestlen - 1; i++) {
			if (!smic_write_next(sc, *cp++))
				return (0);
#ifdef SMIC_DEBUG
			device_printf(sc->ipmi_dev, "SMIC: Wrote data: %02x\n",
			    cp[-1]);
#endif
		}
		if (!smic_write_last(sc, *cp))
			return (0);
#ifdef SMIC_DEBUG
		device_printf(sc->ipmi_dev, "SMIC: Write last data: %02x\n",
		    *cp);
#endif
	}

	/* Start the read phase by reading the NetFn/LUN. */
	if (smic_start_read(sc, &data) != 1)
		return (0);
#ifdef SMIC_DEBUG
	device_printf(sc->ipmi_dev, "SMIC: Read address: %02x\n", data);
#endif
	if (data != IPMI_REPLY_ADDR(req->ir_addr)) {
		device_printf(sc->ipmi_dev, "SMIC: Reply address mismatch\n");
		return (0);
	}

	/* Read the command. */
	if (smic_read_byte(sc, &data) != 1)
		return (0);
#ifdef SMIC_DEBUG
	device_printf(sc->ipmi_dev, "SMIC: Read command: %02x\n", data);
#endif
	if (data != req->ir_command) {
		device_printf(sc->ipmi_dev, "SMIC: Command mismatch\n");
		return (0);
	}

	/* Read the completion code. */
	state = smic_read_byte(sc, &req->ir_compcode);
	if (state == 0)
		return (0);
#ifdef SMIC_DEBUG
	device_printf(sc->ipmi_dev, "SMIC: Read completion code: %02x\n",
	    req->ir_compcode);
#endif

	/* Finally, read the reply from the BMC. */
	i = 0;
	while (state == 1) {
		state = smic_read_byte(sc, &data);
		if (state == 0)
			return (0);
		if (i < req->ir_replybuflen) {
			req->ir_reply[i] = data;
#ifdef SMIC_DEBUG
			device_printf(sc->ipmi_dev, "SMIC: Read data: %02x\n",
			    data);
		} else {
			device_printf(sc->ipmi_dev,
			    "SMIC: Read short %02x byte %d\n", data, i + 1);
#endif
		}
		i++;
	}

	/* Terminate the transfer. */
	if (!smic_read_end(sc))
		return (0);
	req->ir_replylen = i;
#ifdef SMIC_DEBUG
	device_printf(sc->ipmi_dev, "SMIC: READ finished (%d bytes)\n", i);
	if (req->ir_replybuflen < i)
#else
	if (req->ir_replybuflen < i && req->ir_replybuflen != 0)
#endif
		device_printf(sc->ipmi_dev,
		    "SMIC: Read short: %zd buffer, %d actual\n",
		    req->ir_replybuflen, i);
	return (1);
}