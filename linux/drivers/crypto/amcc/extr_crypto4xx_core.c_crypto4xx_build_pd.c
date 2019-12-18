#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct scatterlist {unsigned int const length; int /*<<< orphan*/  offset; } ;
struct pd_uinfo {int num_gd; int num_sd; int sr_pa; int first_gd; int first_sd; int state; struct dynamic_sa_ctl* sa_va; TYPE_1__* sr_va; struct crypto_async_request* async_req; struct scatterlist* dest_va; } ;
struct TYPE_14__ {int gather; int scatter; } ;
struct TYPE_15__ {TYPE_3__ bf; } ;
struct TYPE_19__ {scalar_t__ crypto_mode9_8; unsigned int hash_crypto_offset; } ;
struct TYPE_20__ {TYPE_8__ bf; } ;
struct dynamic_sa_ctl {TYPE_4__ sa_command_0; TYPE_9__ sa_command_1; } ;
struct crypto_async_request {int flags; int /*<<< orphan*/  tfm; } ;
struct crypto4xx_device {int pdr_head; int pdr_tail; int gdr_head; int sdr_head; scalar_t__ ce_base; TYPE_10__* core_dev; struct pd_uinfo* pdr_uinfo; struct ce_pd* pdr; } ;
struct crypto4xx_ctx {struct crypto4xx_device* dev; } ;
struct TYPE_16__ {int rdy; scalar_t__ done; } ;
struct ce_sd {TYPE_5__ ctl; } ;
struct TYPE_18__ {int w; } ;
struct TYPE_17__ {int w; } ;
struct ce_pd {unsigned int sa_len; int src; int dest; TYPE_7__ pd_ctl_len; TYPE_6__ pd_ctl; } ;
struct TYPE_13__ {size_t len; int ready; scalar_t__ done; } ;
struct ce_gd {TYPE_2__ ctl_len; scalar_t__ ptr; } ;
typedef  void* dma_addr_t ;
typedef  struct dynamic_sa_ctl __le32 ;
struct TYPE_12__ {struct dynamic_sa_ctl* save_iv; } ;
struct TYPE_11__ {int /*<<< orphan*/  device; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int const AES_BLOCK_SIZE ; 
 scalar_t__ CRYPTO4XX_INT_DESCR_RD ; 
 scalar_t__ CRYPTO_ALG_TYPE_AEAD ; 
 scalar_t__ CRYPTO_ALG_TYPE_AHASH ; 
 scalar_t__ CRYPTO_MODE_CFB ; 
 scalar_t__ CRYPTO_MODE_OFB ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ERING_WAS_FULL ; 
 int PD_CTL_HASH_FINAL ; 
 int PD_CTL_HOST_READY ; 
 int PD_ENTRY_BUSY ; 
 int PD_ENTRY_INUSE ; 
 int PPC4XX_NUM_PD ; 
 unsigned int const PPC4XX_SD_BUFFER_SIZE ; 
 struct ce_gd* crypto4xx_get_gdp (struct crypto4xx_device*,void**,int) ; 
 int crypto4xx_get_n_gd (struct crypto4xx_device*,int) ; 
 int crypto4xx_get_n_sd (struct crypto4xx_device*,int) ; 
 int crypto4xx_get_pd_from_pdr_nolock (struct crypto4xx_device*) ; 
 struct ce_sd* crypto4xx_get_sdp (struct crypto4xx_device*,void**,int) ; 
 scalar_t__ crypto_tfm_alg_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t get_dynamic_sa_offset_state_ptr_field (struct dynamic_sa_ctl*) ; 
 int get_next_gd (int) ; 
 int get_next_sd (int) ; 
 int /*<<< orphan*/  memcpy (struct dynamic_sa_ctl*,struct dynamic_sa_ctl const*,unsigned int const) ; 
 size_t min (unsigned int const,unsigned int) ; 
 struct scatterlist* scatterwalk_ffwd (struct scatterlist*,struct scatterlist*,unsigned int const) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 int sg_nents_for_len (struct scatterlist*,unsigned int const) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int crypto4xx_build_pd(struct crypto_async_request *req,
		       struct crypto4xx_ctx *ctx,
		       struct scatterlist *src,
		       struct scatterlist *dst,
		       const unsigned int datalen,
		       const __le32 *iv, const u32 iv_len,
		       const struct dynamic_sa_ctl *req_sa,
		       const unsigned int sa_len,
		       const unsigned int assoclen,
		       struct scatterlist *_dst)
{
	struct crypto4xx_device *dev = ctx->dev;
	struct dynamic_sa_ctl *sa;
	struct ce_gd *gd;
	struct ce_pd *pd;
	u32 num_gd, num_sd;
	u32 fst_gd = 0xffffffff;
	u32 fst_sd = 0xffffffff;
	u32 pd_entry;
	unsigned long flags;
	struct pd_uinfo *pd_uinfo;
	unsigned int nbytes = datalen;
	size_t offset_to_sr_ptr;
	u32 gd_idx = 0;
	int tmp;
	bool is_busy, force_sd;

	/*
	 * There's a very subtile/disguised "bug" in the hardware that
	 * gets indirectly mentioned in 18.1.3.5 Encryption/Decryption
	 * of the hardware spec:
	 * *drum roll* the AES/(T)DES OFB and CFB modes are listed as
	 * operation modes for >>> "Block ciphers" <<<.
	 *
	 * To workaround this issue and stop the hardware from causing
	 * "overran dst buffer" on crypttexts that are not a multiple
	 * of 16 (AES_BLOCK_SIZE), we force the driver to use the
	 * scatter buffers.
	 */
	force_sd = (req_sa->sa_command_1.bf.crypto_mode9_8 == CRYPTO_MODE_CFB
		|| req_sa->sa_command_1.bf.crypto_mode9_8 == CRYPTO_MODE_OFB)
		&& (datalen % AES_BLOCK_SIZE);

	/* figure how many gd are needed */
	tmp = sg_nents_for_len(src, assoclen + datalen);
	if (tmp < 0) {
		dev_err(dev->core_dev->device, "Invalid number of src SG.\n");
		return tmp;
	}
	if (tmp == 1)
		tmp = 0;
	num_gd = tmp;

	if (assoclen) {
		nbytes += assoclen;
		dst = scatterwalk_ffwd(_dst, dst, assoclen);
	}

	/* figure how many sd are needed */
	if (sg_is_last(dst) && force_sd == false) {
		num_sd = 0;
	} else {
		if (datalen > PPC4XX_SD_BUFFER_SIZE) {
			num_sd = datalen / PPC4XX_SD_BUFFER_SIZE;
			if (datalen % PPC4XX_SD_BUFFER_SIZE)
				num_sd++;
		} else {
			num_sd = 1;
		}
	}

	/*
	 * The follow section of code needs to be protected
	 * The gather ring and scatter ring needs to be consecutive
	 * In case of run out of any kind of descriptor, the descriptor
	 * already got must be return the original place.
	 */
	spin_lock_irqsave(&dev->core_dev->lock, flags);
	/*
	 * Let the caller know to slow down, once more than 13/16ths = 81%
	 * of the available data contexts are being used simultaneously.
	 *
	 * With PPC4XX_NUM_PD = 256, this will leave a "backlog queue" for
	 * 31 more contexts. Before new requests have to be rejected.
	 */
	if (req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG) {
		is_busy = ((dev->pdr_head - dev->pdr_tail) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 13) / 16);
	} else {
		/*
		 * To fix contention issues between ipsec (no blacklog) and
		 * dm-crypto (backlog) reserve 32 entries for "no backlog"
		 * data contexts.
		 */
		is_busy = ((dev->pdr_head - dev->pdr_tail) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 15) / 16);

		if (is_busy) {
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			return -EBUSY;
		}
	}

	if (num_gd) {
		fst_gd = crypto4xx_get_n_gd(dev, num_gd);
		if (fst_gd == ERING_WAS_FULL) {
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			return -EAGAIN;
		}
	}
	if (num_sd) {
		fst_sd = crypto4xx_get_n_sd(dev, num_sd);
		if (fst_sd == ERING_WAS_FULL) {
			if (num_gd)
				dev->gdr_head = fst_gd;
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			return -EAGAIN;
		}
	}
	pd_entry = crypto4xx_get_pd_from_pdr_nolock(dev);
	if (pd_entry == ERING_WAS_FULL) {
		if (num_gd)
			dev->gdr_head = fst_gd;
		if (num_sd)
			dev->sdr_head = fst_sd;
		spin_unlock_irqrestore(&dev->core_dev->lock, flags);
		return -EAGAIN;
	}
	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	pd = &dev->pdr[pd_entry];
	pd->sa_len = sa_len;

	pd_uinfo = &dev->pdr_uinfo[pd_entry];
	pd_uinfo->num_gd = num_gd;
	pd_uinfo->num_sd = num_sd;
	pd_uinfo->dest_va = dst;
	pd_uinfo->async_req = req;

	if (iv_len)
		memcpy(pd_uinfo->sr_va->save_iv, iv, iv_len);

	sa = pd_uinfo->sa_va;
	memcpy(sa, req_sa, sa_len * 4);

	sa->sa_command_1.bf.hash_crypto_offset = (assoclen >> 2);
	offset_to_sr_ptr = get_dynamic_sa_offset_state_ptr_field(sa);
	*(u32 *)((unsigned long)sa + offset_to_sr_ptr) = pd_uinfo->sr_pa;

	if (num_gd) {
		dma_addr_t gd_dma;
		struct scatterlist *sg;

		/* get first gd we are going to use */
		gd_idx = fst_gd;
		pd_uinfo->first_gd = fst_gd;
		gd = crypto4xx_get_gdp(dev, &gd_dma, gd_idx);
		pd->src = gd_dma;
		/* enable gather */
		sa->sa_command_0.bf.gather = 1;
		/* walk the sg, and setup gather array */

		sg = src;
		while (nbytes) {
			size_t len;

			len = min(sg->length, nbytes);
			gd->ptr = dma_map_page(dev->core_dev->device,
				sg_page(sg), sg->offset, len, DMA_TO_DEVICE);
			gd->ctl_len.len = len;
			gd->ctl_len.done = 0;
			gd->ctl_len.ready = 1;
			if (len >= nbytes)
				break;

			nbytes -= sg->length;
			gd_idx = get_next_gd(gd_idx);
			gd = crypto4xx_get_gdp(dev, &gd_dma, gd_idx);
			sg = sg_next(sg);
		}
	} else {
		pd->src = (u32)dma_map_page(dev->core_dev->device, sg_page(src),
				src->offset, min(nbytes, src->length),
				DMA_TO_DEVICE);
		/*
		 * Disable gather in sa command
		 */
		sa->sa_command_0.bf.gather = 0;
		/*
		 * Indicate gather array is not used
		 */
		pd_uinfo->first_gd = 0xffffffff;
	}
	if (!num_sd) {
		/*
		 * we know application give us dst a whole piece of memory
		 * no need to use scatter ring.
		 */
		pd_uinfo->first_sd = 0xffffffff;
		sa->sa_command_0.bf.scatter = 0;
		pd->dest = (u32)dma_map_page(dev->core_dev->device,
					     sg_page(dst), dst->offset,
					     min(datalen, dst->length),
					     DMA_TO_DEVICE);
	} else {
		dma_addr_t sd_dma;
		struct ce_sd *sd = NULL;

		u32 sd_idx = fst_sd;
		nbytes = datalen;
		sa->sa_command_0.bf.scatter = 1;
		pd_uinfo->first_sd = fst_sd;
		sd = crypto4xx_get_sdp(dev, &sd_dma, sd_idx);
		pd->dest = sd_dma;
		/* setup scatter descriptor */
		sd->ctl.done = 0;
		sd->ctl.rdy = 1;
		/* sd->ptr should be setup by sd_init routine*/
		if (nbytes >= PPC4XX_SD_BUFFER_SIZE)
			nbytes -= PPC4XX_SD_BUFFER_SIZE;
		else
			nbytes = 0;
		while (nbytes) {
			sd_idx = get_next_sd(sd_idx);
			sd = crypto4xx_get_sdp(dev, &sd_dma, sd_idx);
			/* setup scatter descriptor */
			sd->ctl.done = 0;
			sd->ctl.rdy = 1;
			if (nbytes >= PPC4XX_SD_BUFFER_SIZE) {
				nbytes -= PPC4XX_SD_BUFFER_SIZE;
			} else {
				/*
				 * SD entry can hold PPC4XX_SD_BUFFER_SIZE,
				 * which is more than nbytes, so done.
				 */
				nbytes = 0;
			}
		}
	}

	pd->pd_ctl.w = PD_CTL_HOST_READY |
		((crypto_tfm_alg_type(req->tfm) == CRYPTO_ALG_TYPE_AHASH) |
		 (crypto_tfm_alg_type(req->tfm) == CRYPTO_ALG_TYPE_AEAD) ?
			PD_CTL_HASH_FINAL : 0);
	pd->pd_ctl_len.w = 0x00400000 | (assoclen + datalen);
	pd_uinfo->state = PD_ENTRY_INUSE | (is_busy ? PD_ENTRY_BUSY : 0);

	wmb();
	/* write any value to push engine to read a pd */
	writel(0, dev->ce_base + CRYPTO4XX_INT_DESCR_RD);
	writel(1, dev->ce_base + CRYPTO4XX_INT_DESCR_RD);
	return is_busy ? -EBUSY : -EINPROGRESS;
}