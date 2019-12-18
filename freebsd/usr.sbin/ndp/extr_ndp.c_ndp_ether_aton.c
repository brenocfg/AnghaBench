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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ndp_ether_aton(char *a, u_char *n)
{
	int i, o[6];

	i = sscanf(a, "%x:%x:%x:%x:%x:%x", &o[0], &o[1], &o[2],
	    &o[3], &o[4], &o[5]);
	if (i != 6) {
		fprintf(stderr, "ndp: invalid Ethernet address '%s'\n", a);
		return (1);
	}
	for (i = 0; i < 6; i++)
		n[i] = o[i];
	return (0);
}