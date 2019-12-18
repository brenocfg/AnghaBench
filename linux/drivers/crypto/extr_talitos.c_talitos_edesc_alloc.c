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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct talitos_ptr {int dummy; } ;
struct talitos_private {int dummy; } ;
struct talitos_edesc {int src_nents; int dst_nents; int dma_len; int /*<<< orphan*/ * link_tbl; void* dma_link_tbl; void* iv_dma; int /*<<< orphan*/  desc; } ;
struct talitos_desc {int dummy; } ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  int gfp_t ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct talitos_edesc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int TALITOS1_MAX_DATA_LEN ; 
 int TALITOS2_MAX_DATA_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 struct talitos_edesc* kmalloc (int,int) ; 
 int /*<<< orphan*/ * memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sg_nents_for_len (struct scatterlist*,int) ; 

__attribute__((used)) static struct talitos_edesc *talitos_edesc_alloc(struct device *dev,
						 struct scatterlist *src,
						 struct scatterlist *dst,
						 u8 *iv,
						 unsigned int assoclen,
						 unsigned int cryptlen,
						 unsigned int authsize,
						 unsigned int ivsize,
						 int icv_stashing,
						 u32 cryptoflags,
						 bool encrypt)
{
	struct talitos_edesc *edesc;
	int src_nents, dst_nents, alloc_len, dma_len, src_len, dst_len;
	dma_addr_t iv_dma = 0;
	gfp_t flags = cryptoflags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		      GFP_ATOMIC;
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	int max_len = is_sec1 ? TALITOS1_MAX_DATA_LEN : TALITOS2_MAX_DATA_LEN;

	if (cryptlen + authsize > max_len) {
		dev_err(dev, "length exceeds h/w max limit\n");
		return ERR_PTR(-EINVAL);
	}

	if (!dst || dst == src) {
		src_len = assoclen + cryptlen + authsize;
		src_nents = sg_nents_for_len(src, src_len);
		if (src_nents < 0) {
			dev_err(dev, "Invalid number of src SG.\n");
			return ERR_PTR(-EINVAL);
		}
		src_nents = (src_nents == 1) ? 0 : src_nents;
		dst_nents = dst ? src_nents : 0;
		dst_len = 0;
	} else { /* dst && dst != src*/
		src_len = assoclen + cryptlen + (encrypt ? 0 : authsize);
		src_nents = sg_nents_for_len(src, src_len);
		if (src_nents < 0) {
			dev_err(dev, "Invalid number of src SG.\n");
			return ERR_PTR(-EINVAL);
		}
		src_nents = (src_nents == 1) ? 0 : src_nents;
		dst_len = assoclen + cryptlen + (encrypt ? authsize : 0);
		dst_nents = sg_nents_for_len(dst, dst_len);
		if (dst_nents < 0) {
			dev_err(dev, "Invalid number of dst SG.\n");
			return ERR_PTR(-EINVAL);
		}
		dst_nents = (dst_nents == 1) ? 0 : dst_nents;
	}

	/*
	 * allocate space for base edesc plus the link tables,
	 * allowing for two separate entries for AD and generated ICV (+ 2),
	 * and space for two sets of ICVs (stashed and generated)
	 */
	alloc_len = sizeof(struct talitos_edesc);
	if (src_nents || dst_nents || !encrypt) {
		if (is_sec1)
			dma_len = (src_nents ? src_len : 0) +
				  (dst_nents ? dst_len : 0) + authsize;
		else
			dma_len = (src_nents + dst_nents + 2) *
				  sizeof(struct talitos_ptr) + authsize;
		alloc_len += dma_len;
	} else {
		dma_len = 0;
	}
	alloc_len += icv_stashing ? authsize : 0;

	/* if its a ahash, add space for a second desc next to the first one */
	if (is_sec1 && !dst)
		alloc_len += sizeof(struct talitos_desc);
	alloc_len += ivsize;

	edesc = kmalloc(alloc_len, GFP_DMA | flags);
	if (!edesc)
		return ERR_PTR(-ENOMEM);
	if (ivsize) {
		iv = memcpy(((u8 *)edesc) + alloc_len - ivsize, iv, ivsize);
		iv_dma = dma_map_single(dev, iv, ivsize, DMA_TO_DEVICE);
	}
	memset(&edesc->desc, 0, sizeof(edesc->desc));

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->dma_len = dma_len;
	if (dma_len)
		edesc->dma_link_tbl = dma_map_single(dev, &edesc->link_tbl[0],
						     edesc->dma_len,
						     DMA_BIDIRECTIONAL);

	return edesc;
}