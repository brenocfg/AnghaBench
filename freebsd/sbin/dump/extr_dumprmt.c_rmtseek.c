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
 int rmtcall (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

int
rmtseek(int offset, int pos)	/* XXX off_t ? */
{
	char line[80];

	(void)snprintf(line, sizeof (line), "L%d\n%d\n", offset, pos);
	return (rmtcall("seek", line));
}