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
typedef  size_t u_int ;
typedef  size_t u_char ;
struct msgbuf {size_t msg_size; scalar_t__* msg_ptr; } ;

/* Variables and functions */

__attribute__((used)) static u_int
msgbuf_cksum(struct msgbuf *mbp)
{
	u_int i, sum;

	sum = 0;
	for (i = 0; i < mbp->msg_size; i++)
		sum += (u_char)mbp->msg_ptr[i];
	return (sum);
}