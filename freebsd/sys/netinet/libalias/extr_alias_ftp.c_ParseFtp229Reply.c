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
typedef  int u_short ;
struct libalias {int true_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ParseFtp229Reply(struct libalias *la, char *sptr, int dlen)
{
	char ch, delim;
	int i, state;
	u_short port;

	/* Format: "229 Entering Extended Passive Mode (|||PORT|)" */

	/* Return if data length is too short. */
	if (dlen < 11)
		return (0);

	if (strncmp("229 ", sptr, 4))
		return (0);

	port = 0;
	delim = '|';		/* XXX gcc -Wuninitialized */

	state = 0;
	for (i = 4; i < dlen; i++) {
		ch = sptr[i];
		switch (state) {
		case 0:
			if (ch == '(')
				state++;
			break;
		case 1:
			delim = ch;
			state++;
			break;
		case 2:
		case 3:
			if (ch == delim)
				state++;
			else
				return (0);
			break;
		case 4:
			if (isdigit(ch)) {
				port = ch - '0';
				state++;
			} else
				return (0);
			break;
		case 5:
			if (isdigit(ch))
				port = 10 * port + ch - '0';
			else if (ch == delim)
				state++;
			else
				return (0);
			break;
		case 6:
			if (ch == ')')
				state++;
			else
				return (0);
			break;
		}
	}

	if (state == 7) {
		la->true_port = port;
		return (1);
	} else
		return (0);
}