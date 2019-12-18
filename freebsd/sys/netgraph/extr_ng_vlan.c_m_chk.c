#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 

__attribute__((used)) static __inline int
m_chk(struct mbuf **mp, int len)
{

	if ((*mp)->m_pkthdr.len < len) {
		m_freem((*mp));
		(*mp) = NULL;
		return (EINVAL);
	}
	if ((*mp)->m_len < len && ((*mp) = m_pullup((*mp), len)) == NULL)
		return (ENOBUFS);

	return (0);
}