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
struct sockbuf {int dummy; } ;
struct socket {struct sockbuf so_rcv; } ;

/* Variables and functions */

struct sockbuf *
so_sockbuf_rcv(struct socket *so)
{

	return (&so->so_rcv);
}