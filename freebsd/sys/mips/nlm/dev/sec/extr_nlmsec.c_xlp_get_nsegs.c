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
struct uio {int uio_iovcnt; scalar_t__ uio_iov; } ;
struct mbuf {struct mbuf* m_next; int /*<<< orphan*/  m_len; } ;
struct iovec {int /*<<< orphan*/  iov_len; } ;
struct cryptop {int crp_flags; int /*<<< orphan*/  crp_ilen; scalar_t__ crp_buf; } ;

/* Variables and functions */
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 unsigned int NLM_CRYPTO_NUM_SEGS_REQD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xlp_get_nsegs(struct cryptop *crp, unsigned int *nsegs)
{

	if (crp->crp_flags & CRYPTO_F_IMBUF) {
		struct mbuf *m = NULL;

		m = (struct mbuf *)crp->crp_buf;
		while (m != NULL) {
			*nsegs += NLM_CRYPTO_NUM_SEGS_REQD(m->m_len);
			m = m->m_next;
		}
	} else if (crp->crp_flags & CRYPTO_F_IOV) {
		struct uio *uio = NULL;
		struct iovec *iov = NULL;
		int iol = 0;

		uio = (struct uio *)crp->crp_buf;
		iov = (struct iovec *)uio->uio_iov;
		iol = uio->uio_iovcnt;
		while (iol > 0) {
			*nsegs += NLM_CRYPTO_NUM_SEGS_REQD(iov->iov_len);
			iol--;
			iov++;
		}
	} else {
		*nsegs = NLM_CRYPTO_NUM_SEGS_REQD(crp->crp_ilen);
	}
	return (0);
}