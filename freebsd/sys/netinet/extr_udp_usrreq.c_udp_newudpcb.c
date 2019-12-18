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
struct udpcb {int dummy; } ;
struct inpcb {struct udpcb* inp_ppcb; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_udpcb_zone ; 
 struct udpcb* uma_zalloc (int /*<<< orphan*/ ,int) ; 

int
udp_newudpcb(struct inpcb *inp)
{
	struct udpcb *up;

	up = uma_zalloc(V_udpcb_zone, M_NOWAIT | M_ZERO);
	if (up == NULL)
		return (ENOBUFS);
	inp->inp_ppcb = up;
	return (0);
}