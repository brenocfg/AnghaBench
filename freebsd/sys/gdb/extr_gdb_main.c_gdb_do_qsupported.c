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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int gdb_dbfeatures; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ GDB_BUFSZ ; 
 int GDB_DBGP_FEAT_RELIABLE ; 
 TYPE_1__* gdb_cur ; 
 int /*<<< orphan*/ * gdb_feature_names ; 
 char gdb_rx_char () ; 
 char* gdb_rxp ; 
 scalar_t__ gdb_rxsz ; 
 int /*<<< orphan*/  gdb_tx_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_tx_char (char) ; 
 int /*<<< orphan*/  gdb_tx_end () ; 
 int /*<<< orphan*/  gdb_tx_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_tx_str (char*) ; 
 int /*<<< orphan*/  gdb_tx_varhex (scalar_t__) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strchrnul (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
gdb_do_qsupported(uint32_t *feat)
{
	char *tok, *delim, ok;
	size_t i, toklen;

	/* Parse supported host features */
	*feat = 0;
	if (gdb_rx_char() != ':')
		goto error;

	while (gdb_rxsz > 0) {
		tok = gdb_rxp;
		delim = strchrnul(gdb_rxp, ';');
		toklen = (delim - tok);

		gdb_rxp += toklen;
		gdb_rxsz -= toklen;
		if (*delim != '\0') {
			*delim = '\0';
			gdb_rxp += 1;
			gdb_rxsz -= 1;
		}

		if (toklen < 2)
			goto error;

		ok = tok[toklen - 1];
		if (ok != '-' && ok != '+') {
			/*
			 * GDB only has one KV-pair feature, and we don't
			 * support it, so ignore and move on.
			 */
			if (strchr(tok, '=') != NULL)
				continue;
			/* Not a KV-pair, and not a +/- flag?  Malformed. */
			goto error;
		}
		if (ok != '+')
			continue;
		tok[toklen - 1] = '\0';

		for (i = 0; i < nitems(gdb_feature_names); i++)
			if (strcmp(gdb_feature_names[i], tok) == 0)
				break;

		if (i == nitems(gdb_feature_names)) {
			/* Unknown GDB feature. */
			continue;
		}

		*feat |= BIT(i);
	}

	/* Send a supported feature list back */
	gdb_tx_begin(0);

	gdb_tx_str("PacketSize");
	gdb_tx_char('=');
	/*
	 * We don't buffer framing bytes, but we do need to retain a byte for a
	 * trailing nul.
	 */
	gdb_tx_varhex(GDB_BUFSZ + strlen("$#nn") - 1);

	gdb_tx_str(";qXfer:threads:read+");

	/*
	 * If the debugport is a reliable transport, request No Ack mode from
	 * the server.  The server may or may not choose to enter No Ack mode.
	 * https://sourceware.org/gdb/onlinedocs/gdb/Packet-Acknowledgment.html
	 */
	if (gdb_cur->gdb_dbfeatures & GDB_DBGP_FEAT_RELIABLE)
		gdb_tx_str(";QStartNoAckMode+");

	/*
	 * Future consideration:
	 *   - vCont
	 *   - multiprocess
	 */
	gdb_tx_end();
	return;

error:
	*feat = 0;
	gdb_tx_err(EINVAL);
}