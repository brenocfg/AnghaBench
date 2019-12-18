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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rmtape ; 
 int rmtcall (char*,char*) ; 
 int /*<<< orphan*/  rmtconnaborted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
rmtread(char *buf, int count)
{
	char line[30];
	int n, i, cc;

	(void)snprintf(line, sizeof (line), "R%d\n", count);
	n = rmtcall("read", line);
	if (n < 0)
		/* rmtcall() properly sets errno for us on errors. */
		return (n);
	for (i = 0; i < n; i += cc) {
		cc = read(rmtape, buf+i, n - i);
		if (cc <= 0)
			rmtconnaborted(0);
	}
	return (n);
}