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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_LOCK () ; 
 int /*<<< orphan*/  SEND_UNLOCK () ; 
 int /*<<< orphan*/ * V_send_so ; 

__attribute__((used)) static void
send_close(struct socket *so)
{

	SEND_LOCK();
	if (V_send_so)
		V_send_so = NULL;
	SEND_UNLOCK();
}