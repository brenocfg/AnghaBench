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
struct TYPE_3__ {int* eight; } ;
struct TYPE_4__ {TYPE_1__ PH_loc; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int SGE_MAX_WR_LEN ; 

__attribute__((used)) static inline int
mbuf_len16(struct mbuf *m)
{
	int n;

	M_ASSERTPKTHDR(m);
	n = m->m_pkthdr.PH_loc.eight[0];
	MPASS(n > 0 && n <= SGE_MAX_WR_LEN / 16);

	return (n);
}