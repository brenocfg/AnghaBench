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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  etherbuf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/  const*,char*) ; 

char *
ether_sprintf(const u_char *ap)
{
	static char etherbuf[18];
	snprintf(etherbuf, sizeof (etherbuf), "%6D", ap, ":");
	return (etherbuf);
}