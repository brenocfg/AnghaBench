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
struct thread_data {int /*<<< orphan*/  trm; scalar_t__ ppp; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_select ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timetogo ; 

__attribute__((used)) static void *
Monitor(void *v)
{
    struct thread_data *td;
    fd_set f;
    int ret;

    td = (struct thread_data *)v;
    FD_ZERO(&f);
    FD_SET(td->ppp, &f);

    sem_wait(&sem_select);
    while (!timetogo)
        if ((ret = select(td->ppp + 1, &f, NULL, NULL, NULL)) > 0) {
            pthread_kill(td->trm, SIGUSR1);
            sem_wait(&sem_select);
        }

    return NULL;
}