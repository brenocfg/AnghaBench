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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,void*,size_t) ; 

__attribute__((used)) static size_t
readx(int fd, void *buf, size_t nbyte, off_t offset)
{
    ssize_t n;

    if (offset != -1 && lseek(fd, offset, SEEK_SET) != offset)
	err(2, "%s", fname);
    if ((n = read(fd, buf, nbyte)) == -1)
	err(2, "%s", fname);
    return n;
}