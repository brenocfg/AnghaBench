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

__attribute__((used)) static int
print_pwr_desc(u_char *p)
{
	int     len = 1, i;
	u_char mask;
	const char  **expp;
	static const char *pname[] =
	{"Nominal operating supply voltage",
	 "Minimum operating supply voltage",
	 "Maximum operating supply voltage",
	 "Continuous supply current",
	 "Max current average over 1 second",
	 "Max current average over 10 ms",
	 "Power down supply current",
	 "Reserved"
	};
	static const char *vexp[] =
	{"10uV", "100uV", "1mV", "10mV", "100mV", "1V", "10V", "100V"};
	static const char *cexp[] =
	{"10nA", "1uA", "10uA", "100uA", "1mA", "10mA", "100mA", "1A"};
	static const char *mant[] =
	{"1", "1.2", "1.3", "1.5", "2", "2.5", "3", "3.5", "4", "4.5",
	"5", "5.5", "6", "7", "8", "9"};

	mask = *p++;
	expp = vexp;
	for (i = 0; i < 8; i++)
		if (mask & (1 << i)) {
			len++;
			if (i >= 3)
				expp = cexp;
			printf("\t\t%s: ", pname[i]);
			printf("%s x %s",
			    mant[(*p >> 3) & 0xF],
			    expp[*p & 7]);
			while (*p & 0x80) {
				len++;
				p++;
				printf(", ext = 0x%x", *p);
			}
			printf("\n");
			p++;
		}
	return (len);
}