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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  domain ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DOMAIN_BACKUP_FILE ; 
 int MAXHOSTNAMELEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int getdomainname (char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 size_t strnlen (char*,int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
backup_domain(void)
{
	char domain[MAXHOSTNAMELEN];
	int fd;
	size_t l;
	ssize_t r,n = 0;

	memset(domain, 0, sizeof(domain));

	ATF_REQUIRE_EQ(0, getdomainname(domain, sizeof(domain)));
	l = strnlen(domain, MAXHOSTNAMELEN);
	fd = open(DOMAIN_BACKUP_FILE, O_WRONLY | O_CREAT | O_EXCL, 0644);
	ATF_REQUIRE(fd >= 0);
	while ((r = write(fd, domain + n, l - n)) > 0)
		n += r;
	ATF_REQUIRE_EQ(0, r);
	close(fd);
}