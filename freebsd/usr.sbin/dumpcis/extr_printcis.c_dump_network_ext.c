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
typedef  size_t u_int ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  print_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  tpl32 (int*) ; 

__attribute__((used)) static void
dump_network_ext(u_char *p, int len)
{
	static const char *tech[] = {
		"Undefined", "ARCnet", "Ethernet", "Token ring",
		"Localtalk", "FDDI/CDDI", "ATM", "Wireless"
	};
	static const char *media[] = {
		"Undefined", "UTP", "STP", "Thin coax",
		"THICK coax", "Fiber", "900 MHz", "2.4 GHz",
		"5.4 GHz", "Diffuse Infrared", "Point to point Infrared"
	};
	u_int i = 0;

	if (len < 1)
		return;
	switch (p[0]) {
	case 1:			/* Network technology */
		if (len < 2)
			goto err;
		printf("\tNetwork technology: %s\n", tech[p[1] & 7]);
		break;
	case 2:			/* Network speed */
		if (len < 5)
			goto err;
		printf("\tNetwork speed: ");
		print_speed(tpl32(p + 1));
		putchar('\n');
		break;
	case 3:			/* Network media */
		if (len < 2)
			goto err;
		if (p[1] <= 10)
			i = p[1];
		printf("\tNetwork media: %s\n", media[i]);
		break;
	case 4:			/* Node ID */
		if (len <= 2 || len < p[1] + 2)
			goto err;
		printf("\tNetwork node ID:");
		for (i = 0; i < p[1]; i++)
			printf(" %02x", p[i + 2]);
		putchar('\n');
		break;
	case 5:			/* Connector type */
		if (len < 2)
			goto err;
		printf("\tNetwork connector: %s connector standard\n",
		       (p[1] == 0) ? "open" : "closed");
		break;
	err:	/* warning */
		printf("\tWrong length for network extension tuple\n");
		return;
	}
}