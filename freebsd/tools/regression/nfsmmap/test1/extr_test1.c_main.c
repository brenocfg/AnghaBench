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
typedef  char* caddr_t ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 char* mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ write (int,char*,int) ; 

int main(int argc, char** argv)
{
    int fd, fd2;
    caddr_t addr;
    char zeros[4096];
    char ones[200];

    memset(zeros, 0, sizeof zeros);
    memset(ones, 1, sizeof ones);
#if 0
    unlink("test1.data");
    fd = open("test1.data", O_RDWR|O_CREAT, 0666);
    if (fd < 0)
	err(1, "creating file");
    if (write(fd, zeros, sizeof zeros) < 0)
	err(1, "writing zeros");
    close(fd);
#endif

    fd = open("test1.data", O_RDWR);
    if (fd < 0)
	err(1, "opening file");
    if (lseek(fd, 600, SEEK_SET) < 0)
	err(1, "seeking");
	
    if (write(fd, ones, sizeof ones) < 0)
	err(1, "writing ones");

    fsync(fd);

    addr = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
	err(1, "mapping");
    unlink("test1.scratch");
    fd2 = open("test1.scratch", O_RDWR|O_CREAT, 0666);
    if (fd2 < 0)
	err(1, "creating scratch");
    
    if (write(fd2, addr, 4096) < 0)
	err(1, "writing scratch");
}