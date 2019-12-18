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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static u_long
getvers(char *arg)
{
	char *strptr;
	register u_long vers;

	vers = (int) strtol(arg, &strptr, 10);
	if (strptr == arg || *strptr != '\0')
		errx(1, "%s is illegal version number", arg);
	return (vers);
}