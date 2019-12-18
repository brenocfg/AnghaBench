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
typedef  int /*<<< orphan*/  uint64_t ;
struct work_request_hdr {unsigned int wrh_hi; unsigned int wrh_lo; } ;
struct txq_state {size_t pidx; unsigned int gen; } ;
struct tx_sw_desc {int dummy; } ;
struct tx_desc {int /*<<< orphan*/ * flit; } ;
struct sge_txq {size_t size; struct tx_sw_desc* sdesc; struct tx_desc* desc; } ;
struct sg_ent {int dummy; } ;

/* Variables and functions */
 int F_WR_EOP ; 
 int F_WR_SOP ; 
 int V_WR_DATATYPE (int) ; 
 int V_WR_GEN (unsigned int) ; 
 int V_WR_LEN (unsigned int) ; 
 int V_WR_SGLSFLT (int) ; 
 unsigned int WR_FLITS ; 
 scalar_t__ __predict_true (int) ; 
 unsigned int htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_wr_hdr (struct work_request_hdr*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  wr_gen2 (struct tx_desc*,unsigned int) ; 

__attribute__((used)) static void
write_wr_hdr_sgl(unsigned int ndesc, struct tx_desc *txd, struct txq_state *txqs,
    const struct sge_txq *txq, const struct sg_ent *sgl, unsigned int flits,
    unsigned int sgl_flits, unsigned int wr_hi, unsigned int wr_lo)
{

	struct work_request_hdr *wrp = (struct work_request_hdr *)txd;
	struct tx_sw_desc *txsd = &txq->sdesc[txqs->pidx];
	
	if (__predict_true(ndesc == 1)) {
		set_wr_hdr(wrp, htonl(F_WR_SOP | F_WR_EOP | V_WR_DATATYPE(1) |
		    V_WR_SGLSFLT(flits)) | wr_hi,
		    htonl(V_WR_LEN(flits + sgl_flits) | V_WR_GEN(txqs->gen)) |
		    wr_lo);

		wr_gen2(txd, txqs->gen);
		
	} else {
		unsigned int ogen = txqs->gen;
		const uint64_t *fp = (const uint64_t *)sgl;
		struct work_request_hdr *wp = wrp;
		
		wrp->wrh_hi = htonl(F_WR_SOP | V_WR_DATATYPE(1) |
		    V_WR_SGLSFLT(flits)) | wr_hi;
		
		while (sgl_flits) {
			unsigned int avail = WR_FLITS - flits;

			if (avail > sgl_flits)
				avail = sgl_flits;
			memcpy(&txd->flit[flits], fp, avail * sizeof(*fp));
			sgl_flits -= avail;
			ndesc--;
			if (!sgl_flits)
				break;
			
			fp += avail;
			txd++;
			txsd++;
			if (++txqs->pidx == txq->size) {
				txqs->pidx = 0;
				txqs->gen ^= 1;
				txd = txq->desc;
				txsd = txq->sdesc;
			}

			/*
			 * when the head of the mbuf chain
			 * is freed all clusters will be freed
			 * with it
			 */
			wrp = (struct work_request_hdr *)txd;
			wrp->wrh_hi = htonl(V_WR_DATATYPE(1) |
			    V_WR_SGLSFLT(1)) | wr_hi;
			wrp->wrh_lo = htonl(V_WR_LEN(min(WR_FLITS,
				    sgl_flits + 1)) |
			    V_WR_GEN(txqs->gen)) | wr_lo;
			wr_gen2(txd, txqs->gen);
			flits = 1;
		}
		wrp->wrh_hi |= htonl(F_WR_EOP);
		wmb();
		wp->wrh_lo = htonl(V_WR_LEN(WR_FLITS) | V_WR_GEN(ogen)) | wr_lo;
		wr_gen2((struct tx_desc *)wp, ogen);
	}
}