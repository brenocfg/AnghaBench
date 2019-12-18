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
 int /*<<< orphan*/  SEM_BLOCK_NAME ; 
 int /*<<< orphan*/  SEM_COUNT_NAME ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sem_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 scalar_t__ sync_wait (int) ; 
 int wait_timeout ; 

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: shellsync <process num> <wait_timeout>\n");
    }
    else
    {
        int proc_num;
        sscanf(argv[1],"%d",&proc_num);
        sscanf(argv[2],"%d",&wait_timeout);
        if(sync_wait(proc_num)<0)
        {
            printf("Processes sync failed.\n");
            sem_unlink(SEM_COUNT_NAME);
            sem_unlink(SEM_BLOCK_NAME);
            return 1;
        }
        else
        {
            printf("Processes sync succeed.\n");
            return 0;
        }
    }
}