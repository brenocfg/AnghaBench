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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int kern_getsockopt (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
linux_check_hdrincl(struct thread *td, int s)
{
	int error, optval;
	socklen_t size_val;

	size_val = sizeof(optval);
	error = kern_getsockopt(td, s, IPPROTO_IP, IP_HDRINCL,
	    &optval, UIO_SYSSPACE, &size_val);
	if (error != 0)
		return (error);

	return (optval == 0);
}