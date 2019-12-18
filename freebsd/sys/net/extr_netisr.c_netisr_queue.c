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
typedef  int /*<<< orphan*/  u_int ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int netisr_queue_src (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 

int
netisr_queue(u_int proto, struct mbuf *m)
{

	return (netisr_queue_src(proto, 0, m));
}