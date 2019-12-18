#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbchain {TYPE_2__* mb_top; } ;
struct TYPE_3__ {int len; } ;
struct TYPE_4__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int m_fixhdr (TYPE_2__*) ; 

int
mb_fixhdr(struct mbchain *mbp)
{
	return (mbp->mb_top->m_pkthdr.len = m_fixhdr(mbp->mb_top));
}