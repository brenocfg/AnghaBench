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
struct socket_args {int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int kern_socket (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_socket(struct thread *td, struct socket_args *uap)
{

	return (kern_socket(td, uap->domain, uap->type, uap->protocol));
}