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
typedef  int u_short ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct libalias {int true_port; TYPE_1__ true_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
ParseFtpEprtCommand(struct libalias *la, char *sptr, int dlen)
{
	char ch, delim;
	int i, state;
	u_int32_t addr;
	u_short port;
	u_int8_t octet;

	/* Format: "EPRT |1|A.D.D.R|PORT|". */

	/* Return if data length is too short. */
	if (dlen < 18)
		return (0);

	if (strncasecmp("EPRT ", sptr, 5))
		return (0);

	addr = port = octet = 0;
	delim = '|';		/* XXX gcc -Wuninitialized */
	state = 0;
	for (i = 5; i < dlen; i++) {
		ch = sptr[i];
		switch (state) {
		case 0:
			if (!isspace(ch)) {
				delim = ch;
				state++;
			}
			break;
		case 1:
			if (ch == '1')	/* IPv4 address */
				state++;
			else
				return (0);
			break;
		case 2:
			if (ch == delim)
				state++;
			else
				return (0);
			break;
		case 3:
		case 5:
		case 7:
		case 9:
			if (isdigit(ch)) {
				octet = ch - '0';
				state++;
			} else
				return (0);
			break;
		case 4:
		case 6:
		case 8:
		case 10:
			if (isdigit(ch))
				octet = 10 * octet + ch - '0';
			else if (ch == '.' || state == 10) {
				addr = (addr << 8) + octet;
				state++;
			} else
				return (0);
			break;
		case 11:
			if (isdigit(ch)) {
				port = ch - '0';
				state++;
			} else
				return (0);
			break;
		case 12:
			if (isdigit(ch))
				port = 10 * port + ch - '0';
			else if (ch == delim)
				state++;
			else
				return (0);
			break;
		}
	}

	if (state == 13) {
		la->true_addr.s_addr = htonl(addr);
		la->true_port = port;
		return (1);
	} else
		return (0);
}