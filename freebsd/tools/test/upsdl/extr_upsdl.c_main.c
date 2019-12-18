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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  getpagesize () ; 
 scalar_t__ mapBuffer (char**,int,int) ; 
 int /*<<< orphan*/  pagesize ; 
 scalar_t__ prepareFile (char*,int*) ; 
 int startIO (int,char*) ; 

int main(int argc,char *argv[],char *envp[])
{

  int fdA,fdB,fdDelayA,fdDelayB;
  int status;
  char *bufferA,*bufferB;
  pid_t pid;

  pagesize = getpagesize();

  if ((prepareFile("A",&fdA))
      || (prepareFile("B",&fdB))
      || (prepareFile("DelayA",&fdDelayA))
      || (prepareFile("DelayB",&fdDelayB))
      || (mapBuffer(&bufferA,fdDelayA,fdB))
      || (mapBuffer(&bufferB,fdDelayB,fdA)))
    exit(1);
  
  pid = fork();

  if (pid == 0)
    {
      status = startIO(fdA,bufferA);
      exit(status);
    }

  if (pid == -1)
    {
      exit(1);
    }
  status = startIO(fdB,bufferB);
  exit(status);

}