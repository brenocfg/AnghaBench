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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ close (int) ; 
 int openat (int,char const*,int,int) ; 

__attribute__((used)) static void
touchat(int _dirfd, const char *name)
{
	int fd;

	ATF_REQUIRE((fd = openat(_dirfd, name, O_CREAT | O_TRUNC | O_WRONLY,
	    0777)) >= 0);
	ATF_REQUIRE(close(fd) == 0);
}