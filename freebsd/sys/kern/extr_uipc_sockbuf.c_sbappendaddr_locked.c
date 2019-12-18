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
struct sockbuf {int dummy; } ;
struct sockaddr {int sa_len; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 scalar_t__ m_length (struct mbuf*,struct mbuf**) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sbappendaddr_locked_internal (struct sockbuf*,struct sockaddr const*,struct mbuf*,struct mbuf*,struct mbuf*) ; 
 int sbspace (struct sockbuf*) ; 

int
sbappendaddr_locked(struct sockbuf *sb, const struct sockaddr *asa,
    struct mbuf *m0, struct mbuf *control)
{
	struct mbuf *ctrl_last;
	int space = asa->sa_len;

	SOCKBUF_LOCK_ASSERT(sb);

	if (m0 && (m0->m_flags & M_PKTHDR) == 0)
		panic("sbappendaddr_locked");
	if (m0)
		space += m0->m_pkthdr.len;
	space += m_length(control, &ctrl_last);

	if (space > sbspace(sb))
		return (0);
	return (sbappendaddr_locked_internal(sb, asa, m0, control, ctrl_last));
}