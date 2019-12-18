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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,struct in_addr*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extract_ipv4_addr(char *name, uint32_t *addr, uint16_t *port)
{
	struct in_addr a;
	char *pp;

	pp = strchr(name, ':');
	if (pp != NULL) {	/* do we have ports ? */
		*pp++ = '\0';
		*port = (uint16_t)strtol(pp, NULL, 0);
	}

	inet_pton(AF_INET, name, &a);
	*addr = ntohl(a.s_addr);
}