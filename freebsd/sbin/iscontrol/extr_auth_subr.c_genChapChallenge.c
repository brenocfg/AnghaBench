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
typedef  int uint ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 char* bin2str (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  read (int,unsigned char*,int) ; 

char *
genChapChallenge(char *encoding, uint len)
{
     int	fd;
     unsigned	char tmp[1024];

     if(len > sizeof(tmp))
	  return NULL;

     if((fd = open("/dev/random", O_RDONLY)) != -1) {
	  read(fd, tmp, len);
	  close(fd);
	  return bin2str(encoding, tmp, len);
     }
     perror("/dev/random");
     // make up something ...
     return NULL;
}