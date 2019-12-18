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

/* Variables and functions */
 size_t atoi (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

int
main(int argc, char *argv[])
{
	char b[10];
	size_t len =  atoi(argv[1]);
	(void)memset(b, 0, len);
	return b[0]; /* keeps optimizer from zapping the call to memset() */
}