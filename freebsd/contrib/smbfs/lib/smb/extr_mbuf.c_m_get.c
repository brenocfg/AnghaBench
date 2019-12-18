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
struct mbuf {size_t m_maxlen; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t M_ALIGN (size_t) ; 
 scalar_t__ M_BASESIZE ; 
 size_t M_MINSIZE ; 
 int /*<<< orphan*/  M_TOP (struct mbuf*) ; 
 int /*<<< orphan*/  bzero (struct mbuf*,scalar_t__) ; 
 struct mbuf* malloc (scalar_t__) ; 

__attribute__((used)) static int
m_get(size_t len, struct mbuf **mpp)
{
	struct mbuf *m;

	len = M_ALIGN(len);
	if (len < M_MINSIZE)
		len = M_MINSIZE;
	m = malloc(M_BASESIZE + len);
	if (m == NULL)
		return ENOMEM;
	bzero(m, M_BASESIZE + len);
	m->m_maxlen = len;
	m->m_data = M_TOP(m);
	*mpp = m;
	return 0;
}