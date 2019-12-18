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
struct rusage32 {int dummy; } ;
struct rusage {int dummy; } ;
struct freebsd32_getrusage_args {int /*<<< orphan*/  rusage; int /*<<< orphan*/  who; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int copyout (struct rusage32*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freebsd32_rusage_out (struct rusage*,struct rusage32*) ; 
 int kern_getrusage (struct thread*,int /*<<< orphan*/ ,struct rusage*) ; 

int
freebsd32_getrusage(struct thread *td, struct freebsd32_getrusage_args *uap)
{
	struct rusage32 s32;
	struct rusage s;
	int error;

	error = kern_getrusage(td, uap->who, &s);
	if (error == 0) {
		freebsd32_rusage_out(&s, &s32);
		error = copyout(&s32, uap->rusage, sizeof(s32));
	}
	return (error);
}