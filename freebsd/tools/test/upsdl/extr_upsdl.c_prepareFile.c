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
 int /*<<< orphan*/  FILESIZE ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int MS_INVALIDATE ; 
 int MS_SYNC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int fsync (int) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int msync (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  wbuffer ; 
 int write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int prepareFile(char* filename,int* fdp)
{
  int fd;
  int len;
  int status;
  void *addr;

  fd = open(filename,O_CREAT | O_TRUNC | O_RDWR,S_IRWXU);
  if (fd == -1)
    {
      perror("Creating file");
      return fd;
    }
  
  len = write(fd,wbuffer,FILESIZE);
  if (len < 0)
    {
      perror("Write failed");
      return 1;
    }

  status = fsync(fd);
   if (status != 0)
    {
        perror("fsync failed");
	return 1;
    }

  addr = mmap(NULL,FILESIZE, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED)
    {
      perror("Mmap failed");
      return 1;
    }

  status = msync(addr,FILESIZE,MS_INVALIDATE | MS_SYNC);
  if (status != 0)
    {
        perror("Msync failed");
	return 1;
    }

  munmap(addr,FILESIZE);

  *fdp = fd;
  return 0;
}