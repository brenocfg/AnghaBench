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
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ParseFtp227Reply(struct libalias *la, char *sptr, int dlen)
{
	char ch;
	int i, state;
	u_int32_t addr;
	u_short port;
	u_int8_t octet;

	/* Format: "227 Entering Passive Mode (A,D,D,R,PO,RT)" */

	/* Return if data length is too short. */
	if (dlen < 17)
		return (0);

	if (strncmp("227 ", sptr, 4))
		return (0);

	addr = port = octet = 0;

	state = 0;
	for (i = 4; i < dlen; i++) {
		ch = sptr[i];
		switch (state) {
		case 0:
			if (ch == '(')
				state++;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
			if (isdigit(ch)) {
				octet = ch - '0';
				state++;
			} else
				return (0);
			break;
		case 2:
		case 4:
		case 6:
		case 8:
			if (isdigit(ch))
				octet = 10 * octet + ch - '0';
			else if (ch == ',') {
				addr = (addr << 8) + octet;
				state++;
			} else
				return (0);
			break;
		case 10:
		case 12:
			if (isdigit(ch))
				octet = 10 * octet + ch - '0';
			else if (ch == ',' || (state == 12 && ch == ')')) {
				port = (port << 8) + octet;
				state++;
			} else
				return (0);
			break;
		}
	}

	if (state == 13) {
		la->true_port = port;
		la->true_addr.s_addr = htonl(addr);
		return (1);
	} else
		return (0);
}