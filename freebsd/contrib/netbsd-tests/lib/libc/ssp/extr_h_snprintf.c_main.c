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
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

int
main(int argc, char *argv[])
{
	char b[10];
	size_t len = atoi(argv[1]);
#ifdef __FreeBSD__
	char c[] = "01234567890123456789";
	c[len] = 0;
	(void)snprintf(b, len, "%s", c);
#else
	(void)snprintf(b, len, "%s", "0123456789");
#endif
	(void)printf("%s\n", b);
	return 0;
}