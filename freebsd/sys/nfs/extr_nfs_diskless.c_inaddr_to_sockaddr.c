#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 char* kern_getenv (char*) ; 
 int sscanf (char*,char*,int*,int*,int*,int*) ; 

__attribute__((used)) static int
inaddr_to_sockaddr(char *ev, struct sockaddr_in *sa)
{
	u_int32_t a[4];
	char *cp;
	int count;

	bzero(sa, sizeof(*sa));
	sa->sin_len = sizeof(*sa);
	sa->sin_family = AF_INET;

	if ((cp = kern_getenv(ev)) == NULL)
		return (1);
	count = sscanf(cp, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
	freeenv(cp);
	if (count != 4)
		return (1);
	sa->sin_addr.s_addr =
	    htonl((a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3]);
	return (0);
}