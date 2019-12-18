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
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int M_EOR ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SCTP_FROM_SCTP_OUTPUT ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_last (struct mbuf*) ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 struct mbuf* m_uiotombuf (struct uio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mbuf *
sctp_copy_resume(struct uio *uio,
    int max_send_len,
    int user_marks_eor,
    int *error,
    uint32_t *sndout,
    struct mbuf **new_tail)
{
	struct mbuf *m;

	m = m_uiotombuf(uio, M_WAITOK, max_send_len, 0,
	    (M_PKTHDR | (user_marks_eor ? M_EOR : 0)));
	if (m == NULL) {
		SCTP_LTRACE_ERR_RET(NULL, NULL, NULL, SCTP_FROM_SCTP_OUTPUT, ENOBUFS);
		*error = ENOBUFS;
	} else {
		*sndout = m_length(m, NULL);
		*new_tail = m_last(m);
	}
	return (m);
}