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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_addr; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MNAMELEN ; 
 int /*<<< orphan*/  bcopy (struct in_addr const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ getip (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setfs(struct sockaddr_in *addr, char *path, char *p,
    const struct in_addr *siaddr)
{

	if (getip(&p, &addr->sin_addr) == 0) {
		if (siaddr != NULL && *p == '/')
			bcopy(siaddr, &addr->sin_addr, sizeof(struct in_addr));
		else
			return 0;
	} else {
		if (*p != ':')
			return 0;
		p++;
	}
		
	addr->sin_len = sizeof(struct sockaddr_in);
	addr->sin_family = AF_INET;

	strlcpy(path, p, MNAMELEN);
	return 1;
}