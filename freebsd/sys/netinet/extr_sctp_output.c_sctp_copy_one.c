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
struct uio {int dummy; } ;
struct sctp_stream_queue_pending {int /*<<< orphan*/ * data; int /*<<< orphan*/  tail_mbuf; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SCTP_FROM_SCTP_OUTPUT ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * m_uiotombuf (struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sctp_copy_one(struct sctp_stream_queue_pending *sp,
    struct uio *uio,
    int resv_upfront)
{
	sp->data = m_uiotombuf(uio, M_WAITOK, sp->length,
	    resv_upfront, 0);
	if (sp->data == NULL) {
		SCTP_LTRACE_ERR_RET(NULL, NULL, NULL, SCTP_FROM_SCTP_OUTPUT, ENOBUFS);
		return (ENOBUFS);
	}

	sp->tail_mbuf = m_last(sp->data);
	return (0);
}