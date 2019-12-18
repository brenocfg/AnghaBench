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
struct portselect {char* ps_type; scalar_t__ ps_baud; } ;
typedef  int /*<<< orphan*/  baud ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  alarm (int) ; 
 struct portselect* portspeeds ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

const char *
portselector(void)
{
	char c, baud[20];
	const char *type = "default";
	struct portselect *ps;
	size_t len;

	alarm(5*60);
	for (len = 0; len < sizeof (baud) - 1; len++) {
		if (read(STDIN_FILENO, &c, 1) <= 0)
			break;
		c &= 0177;
		if (c == '\n' || c == '\r')
			break;
		if (c == 'B')
			len = 0;	/* in case of leading garbage */
		baud[len] = c;
	}
	baud[len] = '\0';
	for (ps = portspeeds; ps->ps_baud; ps++)
		if (strcmp(ps->ps_baud, baud) == 0) {
			type = ps->ps_type;
			break;
		}
	sleep(2);	/* wait for connection to complete */
	return (type);
}