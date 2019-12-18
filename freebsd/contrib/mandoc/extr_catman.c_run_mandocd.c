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
typedef  int /*<<< orphan*/  sockfdstr ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char const*,char*,char const*,...) ; 
 int snprintf (char*,int,char*,int) ; 

void
run_mandocd(int sockfd, const char *outtype, const char* defos)
{
	char	 sockfdstr[10];

	if (snprintf(sockfdstr, sizeof(sockfdstr), "%d", sockfd) == -1)
		err(1, "snprintf");
	if (defos == NULL)
		execlp("mandocd", "mandocd", "-T", outtype,
		    sockfdstr, (char *)NULL);
	else
		execlp("mandocd", "mandocd", "-T", outtype,
		    "-I", defos, sockfdstr, (char *)NULL);
	err(1, "exec");
}