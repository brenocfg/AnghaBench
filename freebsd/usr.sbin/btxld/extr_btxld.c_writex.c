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

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tname ; 
 int write (int,void const*,size_t) ; 

__attribute__((used)) static void
writex(int fd, const void *buf, size_t nbyte)
{
    ssize_t n;

    if ((n = write(fd, buf, nbyte)) == -1)
	err(2, "%s", tname);
    if ((size_t)n != nbyte)
	errx(2, "%s: Short write", tname);
}