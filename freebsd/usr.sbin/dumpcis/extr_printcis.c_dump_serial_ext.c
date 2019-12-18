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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_serial_ext(u_char *p, int len)
{
	static const char *type[] = {
		"", "Modem", "Data", "Fax", "Voice", "Data modem",
		"Fax/modem", "Voice", " (Data)", " (Fax)", " (Voice)"
	};

	if (len < 1)
		return;
	switch (p[0]) {
	case 0:			/* Serial */
	case 8:			/* Data */
	case 9:			/* Fax */
	case 10:		/* Voice */
		printf("\tSerial interface extension:%s\n", type[*p]);
		if (len < 4)
			goto err;
		switch (p[1] & 0x1F) {
		default:
			printf("\t\tUnknown device");
			break;
		case 0:
			printf("\t\t8250 UART");
			break;
		case 1:
			printf("\t\t16450 UART");
			break;
		case 2:
			printf("\t\t16550 UART");
			break;
		}
		printf(", Parity - %s%s%s%s\n",
		       (p[2] & 1) ? "Space," : "",
		       (p[2] & 2) ? "Mark," : "",
		       (p[2] & 4) ? "Odd," : "",
		       (p[2] & 8) ? "Even" : "");
		printf("\t\tData bit - %s%s%s%s Stop bit - %s%s%s\n",
		       (p[3] & 1) ? "5bit," : "",
		       (p[3] & 2) ? "6bit," : "",
		       (p[3] & 4) ? "7bit," : "",
		       (p[3] & 8) ? "8bit," : "",
		       (p[3] & 0x10) ? "1bit," : "",
		       (p[3] & 0x20) ? "1.5bit," : "",
		       (p[3] & 0x40) ? "2bit" : "");
		break;
	case 1:			/* Serial */
	case 5:			/* Data */
	case 6:			/* Fax */
	case 7:			/* Voice */
		printf("\t%s interface capabilities:\n", type[*p]);
		if (len < 9)
			goto err;
		break;
	case 2:			/* Data */
		printf("\tData modem services available:\n");
		break;
	case 0x13:		/* Fax1 */
	case 0x23:		/* Fax2 */
	case 0x33:		/* Fax3 */
		printf("\tFax%d/modem services available:\n", *p >> 4);
		break;
	case 0x84:		/* Voice */
		printf("\tVoice services available:\n");
		break;
	err:	/* warning */
		printf("\tWrong length for serial extension tuple\n");
		return;
	}
}