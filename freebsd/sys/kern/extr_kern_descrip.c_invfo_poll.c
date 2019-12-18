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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int poll_no_poll (int) ; 

int
invfo_poll(struct file *fp, int events, struct ucred *active_cred,
    struct thread *td)
{

	return (poll_no_poll(events));
}