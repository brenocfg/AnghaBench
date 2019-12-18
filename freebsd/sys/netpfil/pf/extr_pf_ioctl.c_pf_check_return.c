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
typedef  int /*<<< orphan*/  pfil_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFIL_CONSUMED ; 
 int /*<<< orphan*/  PFIL_DROPPED ; 
 int /*<<< orphan*/  PFIL_PASS ; 
#define  PF_PASS 128 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static pfil_return_t
pf_check_return(int chk, struct mbuf **m)
{

	switch (chk) {
	case PF_PASS:
		if (*m == NULL)
			return (PFIL_CONSUMED);
		else
			return (PFIL_PASS);
		break;
	default:
		if (*m != NULL) {
			m_freem(*m);
			*m = NULL;
		}
		return (PFIL_DROPPED);
	}
}