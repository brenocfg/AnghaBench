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
struct TYPE_2__ {int /*<<< orphan*/  (* gdb_putc ) (char) ;int /*<<< orphan*/ * gdb_sendpacket; } ;

/* Variables and functions */
 char N2C (unsigned char) ; 
 int /*<<< orphan*/  gdb_ackmode ; 
 TYPE_1__* gdb_cur ; 
 unsigned char gdb_getc () ; 
 int /*<<< orphan*/  gdb_tx_sendpacket () ; 
 char* gdb_txbuf ; 
 char const* gdb_txp ; 
 int /*<<< orphan*/  stub1 (char) ; 
 int /*<<< orphan*/  stub10 (int) ; 
 int /*<<< orphan*/  stub11 (char) ; 
 int /*<<< orphan*/  stub12 (char) ; 
 int /*<<< orphan*/  stub13 (char) ; 
 int /*<<< orphan*/  stub2 (unsigned char) ; 
 int /*<<< orphan*/  stub3 (char) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int /*<<< orphan*/  stub5 (unsigned char) ; 
 int /*<<< orphan*/  stub6 (unsigned char) ; 
 int /*<<< orphan*/  stub7 (unsigned char) ; 
 int /*<<< orphan*/  stub8 (unsigned char) ; 
 int /*<<< orphan*/  stub9 (char) ; 

int
gdb_tx_end(void)
{
	const char *p;
	int runlen;
	unsigned char c, cksum;

	do {
		if (gdb_cur->gdb_sendpacket != NULL) {
			gdb_tx_sendpacket();
			goto getack;
		}

		gdb_cur->gdb_putc('$');

		cksum = 0;
		p = gdb_txbuf;
		while (p < gdb_txp) {
			/* Send a character and start run-length encoding. */
			c = *p++;
			gdb_cur->gdb_putc(c);
			cksum += c;
			runlen = 0;
			/* Determine run-length and update checksum. */
			while (p < gdb_txp && *p == c) {
				runlen++;
				p++;
			}
			/* Emit the run-length encoded string. */
			while (runlen >= 97) {
				gdb_cur->gdb_putc('*');
				cksum += '*';
				gdb_cur->gdb_putc(97+29);
				cksum += 97+29;
				runlen -= 97;
				if (runlen > 0) {
					gdb_cur->gdb_putc(c);
					cksum += c;
					runlen--;
				}
			}
			if (runlen == 1) {
				gdb_cur->gdb_putc(c);
				cksum += c;
				runlen--;
			}
			if (runlen == 0)
				continue;
			/* Don't emit '$', '#', '+' or '-'. */
			if (runlen == 7) {
				gdb_cur->gdb_putc(c);
				cksum += c;
				runlen--;
			}
			if (runlen == 6 || runlen == 14 || runlen == 16) {
				gdb_cur->gdb_putc(c);
				cksum += c;
				runlen--;
			}
			gdb_cur->gdb_putc('*');
			cksum += '*';
			gdb_cur->gdb_putc(runlen+29);
			cksum += runlen+29;
		}

		gdb_cur->gdb_putc('#');
		c = cksum >> 4;
		gdb_cur->gdb_putc(N2C(c));
		c = cksum & 0x0f;
		gdb_cur->gdb_putc(N2C(c));

getack:
		/*
		 * In NoAckMode, it is assumed that the underlying transport is
		 * reliable and thus neither conservant sends acknowledgements;
		 * there is nothing to wait for here.
		 */
		if (!gdb_ackmode)
			break;

		c = gdb_getc();
	} while (c != '+');

	return (0);
}