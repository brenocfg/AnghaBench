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
 int /*<<< orphan*/  DOMAIN_BACKUP_FILE ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 scalar_t__ setdomainname (char*,int) ; 

__attribute__((used)) static void
restore_domain(void)
{
	char domain[MAXHOSTNAMELEN];
	int fd;
	ssize_t r, n = 0;

	memset(domain, 0, sizeof(domain));
	if ((fd = open(DOMAIN_BACKUP_FILE, O_RDONLY)) < 0)
		err(1, "open");
	while ((r = read(fd, domain + n, sizeof(domain) - n)) > 0)
		n += r;
	if (r < 0)
		err(1, "read");
	if (setdomainname(domain, n) != 0)
		err(1, "setdomainname");
	close(fd);
}