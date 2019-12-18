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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _commit (int) ; 
 int errno ; 
 int /*<<< orphan*/  fsync (int) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 scalar_t__ write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scrub_file (int fd)
{
    off_t pos;
    char buf[128];

    pos = lseek(fd, 0, SEEK_END);
    if (pos < 0)
        return errno;
    if (lseek(fd, 0, SEEK_SET) < 0)
        return errno;
    memset(buf, 0, sizeof(buf));
    while(pos > 0) {
        ssize_t tmp = write(fd, buf, min((off_t)sizeof(buf), pos));

	if (tmp < 0)
	    return errno;
	pos -= tmp;
    }
#ifdef _MSC_VER
    _commit (fd);
#else
    fsync (fd);
#endif
    return 0;
}