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
 int AF_INET ; 
 int AF_INET6 ; 
 int inet_pton (int,char*,void*) ; 
 int /*<<< orphan*/  print_error () ; 
 int /*<<< orphan*/  print_usage () ; 
 char* strchr (char*,char) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_str(int af, char *str, void *addr, unsigned long *mask)
{
	int ret;
	char *slash;

	/* Split the address at the slash. */
	if ((slash = strchr(str, '/')) == NULL)
		print_usage();
	*slash = '\0';

	/* Parse the address. */
	if ((ret = inet_pton(af, str, addr)) != 1) {
		if (ret == 0)
			print_usage();
		else
			print_error();
	}

	/* Parse the mask. */
	*mask = strtoul(slash+1, NULL, 10);
	if ((af == AF_INET  && *mask >  32) ||
		(af == AF_INET6 && *mask > 128))
		print_usage();
}