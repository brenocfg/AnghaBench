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
typedef  int u_int ;

/* Variables and functions */
 int dbprog_discid () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
cdid(void)
{
	u_int	id;

	id = dbprog_discid();
	if (id)
	{
		if (verbose)
			printf ("CDID=");
		printf ("%08x\n",id);
	}
	return id ? 0 : 1;
}