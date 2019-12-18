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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int ALTERA_ETHERNET_OPTION_BITS_OFF ; 
 int /*<<< orphan*/  KENV_GET ; 
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int* block ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ gflag ; 
 int kenv (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  print_eaddr () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_block () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  write_block () ; 

__attribute__((used)) static void
_set(uint8_t *eaddr)
{
	uint8_t buf[32];
	MD5_CTX ctx;
	int rc;

	printf("Original:\n");
	read_block();
	print_eaddr();

	if (eaddr == NULL) {
		/* cfi0.factory_ppr="0x0123456789abcdef" */
		rc = kenv(KENV_GET, "cfi0.factory_ppr", buf, sizeof(buf));
		if (rc == -1)
			err(1, "Could not find Intel flash PPR serial\n");

		MD5Init(&ctx);
		MD5Update(&ctx, buf+2, 16);
		MD5Final(buf, &ctx);
		
		/* Set the device specifc address (prefix). */
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 7] =
		    buf[14] << 4 | buf[13] >> 4;
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 8] =
		    buf[13] << 4 | buf[12] >> 4;
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 9] = buf[12] << 4;
		/* Just make sure the last half-byte is really zero. */
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 9] &= ~0x0f;

		/* Set (or clear) locally administred flag. */
		if (gflag == 0)
			block[ALTERA_ETHERNET_OPTION_BITS_OFF + 4] |= 2;
		else
			block[ALTERA_ETHERNET_OPTION_BITS_OFF + 4] &= ~2;
		/* Make sure it is not a MC address by accident we start with. */
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 4] &= ~1;
	} else {
		int e;

		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 4] = eaddr[0];
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 5] = eaddr[1];
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 6] = eaddr[2];
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 7] = eaddr[3];
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 8] = eaddr[4];
		block[ALTERA_ETHERNET_OPTION_BITS_OFF + 9] = eaddr[5];

		e = 0;
		if ((eaddr[5] & 0xf) != 0x0) {
			e++;
			warnx("WARN: Selected Ethernet Address is "
			    "not multi-MAC compatible.\n");
		}
		if (gflag == 0 && ((eaddr[0] & 0x2) == 0x0)) {
			e++;
			warnx("WARN: Locally administered bit not set.\n");
		}
		if ((eaddr[0] & 0x1) != 0x0) {
			e++;
			warnx("WARN: You are setting a Multicast address.\n");
		}
		if (e != 0)
			warnx("Suggesting to re-run with: "
			    "%02x:%02x:%02x:%02x:%02x:%02x",
			    (eaddr[0] & 0xfe) | 0x2,
			    eaddr[1], eaddr[2], eaddr[3], eaddr[4],
			    eaddr[5] & 0xf0);
	}

	/* Write the "safe" out, just to be sure. */
	block[ALTERA_ETHERNET_OPTION_BITS_OFF + 0] = 0xfe;
	block[ALTERA_ETHERNET_OPTION_BITS_OFF + 1] = 0x5a;
	block[ALTERA_ETHERNET_OPTION_BITS_OFF + 2] = 0x00;
	block[ALTERA_ETHERNET_OPTION_BITS_OFF + 3] = 0x00;

	write_block();

	printf("Updated to:\n");
	read_block();
	print_eaddr();
	exit(0);
}