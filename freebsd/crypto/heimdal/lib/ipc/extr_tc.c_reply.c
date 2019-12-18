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
typedef  int /*<<< orphan*/  heim_isemaphore ;
typedef  int /*<<< orphan*/  heim_idata ;
typedef  int /*<<< orphan*/  heim_icred ;

/* Variables and functions */
 int /*<<< orphan*/  heim_ipc_semaphore_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
reply(void *ctx, int errorcode, heim_idata *reply, heim_icred cred)
{
    printf("got reply\n");
    heim_ipc_semaphore_signal((heim_isemaphore)ctx); /* tell caller we are done */
}