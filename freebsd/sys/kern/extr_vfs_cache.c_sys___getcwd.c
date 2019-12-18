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
struct thread {int dummy; } ;
struct __getcwd_args {int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern___getcwd (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys___getcwd(struct thread *td, struct __getcwd_args *uap)
{

	return (kern___getcwd(td, uap->buf, UIO_USERSPACE, uap->buflen,
	    MAXPATHLEN));
}