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
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int data ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pppdead ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_select ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ want_sem_post ; 

__attribute__((used)) static const char *
SmartGets(EditLine *e, int *count, int fd)
{
    const char *result;

    if (setjmp(pppdead))
        result = NULL;
    else {
        data = fd;
        if (want_sem_post)
            /* Let the Monitor thread in again */
            sem_post(&sem_select);
        result = el_gets(e, count);
    }

    data = -1;

    return result;
}