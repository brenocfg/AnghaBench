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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ADD_ENTROPY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  arc4_addrandom (unsigned char*,int) ; 
 int arc4_seeded_ok ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  evutil_memclear_ (unsigned char*,int) ; 
 int evutil_open_closeonexec_ (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read_all (int,unsigned char*,int) ; 

__attribute__((used)) static int arc4_seed_urandom_helper_(const char *fname)
{
	unsigned char buf[ADD_ENTROPY];
	int fd;
	size_t n;

	fd = evutil_open_closeonexec_(fname, O_RDONLY, 0);
	if (fd<0)
		return -1;
	n = read_all(fd, buf, sizeof(buf));
	close(fd);
	if (n != sizeof(buf))
		return -1;
	arc4_addrandom(buf, sizeof(buf));
	evutil_memclear_(buf, sizeof(buf));
	arc4_seeded_ok = 1;
	return 0;
}