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
typedef  int /*<<< orphan*/  val ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_CORK ; 
 int /*<<< orphan*/  kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void drbd_tcp_cork(struct socket *sock)
{
	int val = 1;
	(void) kernel_setsockopt(sock, SOL_TCP, TCP_CORK,
			(char*)&val, sizeof(val));
}