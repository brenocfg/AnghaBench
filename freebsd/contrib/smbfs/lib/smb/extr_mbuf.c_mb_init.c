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
struct mbuf {int dummy; } ;
struct mbdata {int dummy; } ;

/* Variables and functions */
 int m_get (size_t,struct mbuf**) ; 
 int mb_initm (struct mbdata*,struct mbuf*) ; 

int
mb_init(struct mbdata *mbp, size_t size)
{
	struct mbuf *m;
	int error;

	if ((error = m_get(size, &m)) != 0)
		return error;
	return mb_initm(mbp, m);
}