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
typedef  void* uint8_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  _set (void**) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 char* strsep (char**,char*) ; 
 void* strtol (char*,char**,int) ; 

__attribute__((used)) static void
set(char *eaddrstr)
{
	uint8_t eaddr[ETHER_ADDR_LEN];
	char *p;
	long l;
	int i;

	memset(eaddr, 0x00, ETHER_ADDR_LEN);
	i = 0;
	while ((p = strsep(&eaddrstr, ":")) != NULL && i < ETHER_ADDR_LEN) {
		errno = 0;
		l = strtol(p, (char **)NULL, 16);
		if (l == 0 && errno != 0)
			errx(1, "Failed to parse Ethernet address given: %s\n", p);
		if (l < 0x00 || l > 0xff)
			errx(1, "Failed to parse Ethernet address given: %lx\n", l);
		eaddr[i++] = strtol(p, (char **)NULL, 16);
	}

	if (i != ETHER_ADDR_LEN)
		errx(1, "Failed to parse Ethernet address given\n");

	_set(eaddr);
	exit(0);
}