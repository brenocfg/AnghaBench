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
struct netif {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
net_match(struct netif *nif, void *machdep_hint)
{
	char **a = (char **)machdep_hint;

	if (memcmp("net", *a, 3) == 0)
		return (1);

	printf("net_match: could not match network device\n");
	return (0);
}