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
typedef  scalar_t__ u_int ;
typedef  int u_char ;
struct sshbuf {int dummy; } ;
struct ssh_channels {scalar_t__ x11_refuse_time; scalar_t__ x11_fake_data_len; scalar_t__ x11_saved_data_len; int /*<<< orphan*/  x11_saved_data; int /*<<< orphan*/  x11_fake_data; int /*<<< orphan*/  x11_saved_proto; } ;
struct ssh {struct ssh_channels* chanctxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug2 (char*,...) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ monotime () ; 
 int sshbuf_len (struct sshbuf*) ; 
 int* sshbuf_mutable_ptr (struct sshbuf*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ timingsafe_bcmp (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  verbose (char*) ; 

__attribute__((used)) static int
x11_open_helper(struct ssh *ssh, struct sshbuf *b)
{
	struct ssh_channels *sc = ssh->chanctxt;
	u_char *ucp;
	u_int proto_len, data_len;

	/* Is this being called after the refusal deadline? */
	if (sc->x11_refuse_time != 0 &&
	    (u_int)monotime() >= sc->x11_refuse_time) {
		verbose("Rejected X11 connection after ForwardX11Timeout "
		    "expired");
		return -1;
	}

	/* Check if the fixed size part of the packet is in buffer. */
	if (sshbuf_len(b) < 12)
		return 0;

	/* Parse the lengths of variable-length fields. */
	ucp = sshbuf_mutable_ptr(b);
	if (ucp[0] == 0x42) {	/* Byte order MSB first. */
		proto_len = 256 * ucp[6] + ucp[7];
		data_len = 256 * ucp[8] + ucp[9];
	} else if (ucp[0] == 0x6c) {	/* Byte order LSB first. */
		proto_len = ucp[6] + 256 * ucp[7];
		data_len = ucp[8] + 256 * ucp[9];
	} else {
		debug2("Initial X11 packet contains bad byte order byte: 0x%x",
		    ucp[0]);
		return -1;
	}

	/* Check if the whole packet is in buffer. */
	if (sshbuf_len(b) <
	    12 + ((proto_len + 3) & ~3) + ((data_len + 3) & ~3))
		return 0;

	/* Check if authentication protocol matches. */
	if (proto_len != strlen(sc->x11_saved_proto) ||
	    memcmp(ucp + 12, sc->x11_saved_proto, proto_len) != 0) {
		debug2("X11 connection uses different authentication protocol.");
		return -1;
	}
	/* Check if authentication data matches our fake data. */
	if (data_len != sc->x11_fake_data_len ||
	    timingsafe_bcmp(ucp + 12 + ((proto_len + 3) & ~3),
		sc->x11_fake_data, sc->x11_fake_data_len) != 0) {
		debug2("X11 auth data does not match fake data.");
		return -1;
	}
	/* Check fake data length */
	if (sc->x11_fake_data_len != sc->x11_saved_data_len) {
		error("X11 fake_data_len %d != saved_data_len %d",
		    sc->x11_fake_data_len, sc->x11_saved_data_len);
		return -1;
	}
	/*
	 * Received authentication protocol and data match
	 * our fake data. Substitute the fake data with real
	 * data.
	 */
	memcpy(ucp + 12 + ((proto_len + 3) & ~3),
	    sc->x11_saved_data, sc->x11_saved_data_len);
	return 1;
}