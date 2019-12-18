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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct uio {int uio_iovcnt; TYPE_1__* uio_iov; } ;
struct swcr_data {scalar_t__ sw_size; struct comp_algo* sw_cxf; } ;
struct mbuf {int dummy; } ;
struct cryptodesc {scalar_t__ crd_len; int crd_flags; int /*<<< orphan*/  crd_skip; } ;
struct comp_algo {scalar_t__ (* compress ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ;scalar_t__ (* decompress ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ;} ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */
 int CRD_F_COMP ; 
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  crypto_copyback (int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_copydata (int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
swcr_compdec(struct cryptodesc *crd, struct swcr_data *sw,
    caddr_t buf, int flags)
{
	u_int8_t *data, *out;
	struct comp_algo *cxf;
	int adj;
	u_int32_t result;

	cxf = sw->sw_cxf;

	/* We must handle the whole buffer of data in one time
	 * then if there is not all the data in the mbuf, we must
	 * copy in a buffer.
	 */

	data = malloc(crd->crd_len, M_CRYPTO_DATA,  M_NOWAIT);
	if (data == NULL)
		return (EINVAL);
	crypto_copydata(flags, buf, crd->crd_skip, crd->crd_len, data);

	if (crd->crd_flags & CRD_F_COMP)
		result = cxf->compress(data, crd->crd_len, &out);
	else
		result = cxf->decompress(data, crd->crd_len, &out);

	free(data, M_CRYPTO_DATA);
	if (result == 0)
		return EINVAL;

	/* Copy back the (de)compressed data. m_copyback is
	 * extending the mbuf as necessary.
	 */
	sw->sw_size = result;
	/* Check the compressed size when doing compression */
	if (crd->crd_flags & CRD_F_COMP) {
		if (result >= crd->crd_len) {
			/* Compression was useless, we lost time */
			free(out, M_CRYPTO_DATA);
			return 0;
		}
	}

	crypto_copyback(flags, buf, crd->crd_skip, result, out);
	if (result < crd->crd_len) {
		adj = result - crd->crd_len;
		if (flags & CRYPTO_F_IMBUF) {
			adj = result - crd->crd_len;
			m_adj((struct mbuf *)buf, adj);
		} else if (flags & CRYPTO_F_IOV) {
			struct uio *uio = (struct uio *)buf;
			int ind;

			adj = crd->crd_len - result;
			ind = uio->uio_iovcnt - 1;

			while (adj > 0 && ind >= 0) {
				if (adj < uio->uio_iov[ind].iov_len) {
					uio->uio_iov[ind].iov_len -= adj;
					break;
				}

				adj -= uio->uio_iov[ind].iov_len;
				uio->uio_iov[ind].iov_len = 0;
				ind--;
				uio->uio_iovcnt--;
			}
		}
	}
	free(out, M_CRYPTO_DATA);
	return 0;
}