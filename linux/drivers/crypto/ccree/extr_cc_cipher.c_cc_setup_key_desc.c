#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_5__ {int op_type; } ;
struct cipher_req_ctx {TYPE_1__ gen_ctx; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  key1_slot; } ;
struct TYPE_7__ {int /*<<< orphan*/  slot; } ;
struct TYPE_6__ {int /*<<< orphan*/  key_dma_addr; } ;
struct cc_cipher_ctx {int cipher_mode; int flow_mode; unsigned int keylen; TYPE_4__ hw; TYPE_3__ cpp; TYPE_2__ user; int /*<<< orphan*/  drvdata; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int AES_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  CC_HW_PROTECTED_KEY ; 
 int /*<<< orphan*/  CC_POLICY_PROTECTED_KEY ; 
 int /*<<< orphan*/  DMA_DLLI ; 
#define  DRV_CIPHER_BITLOCKER 135 
#define  DRV_CIPHER_CBC 134 
#define  DRV_CIPHER_CBC_CTS 133 
#define  DRV_CIPHER_CTR 132 
#define  DRV_CIPHER_ECB 131 
#define  DRV_CIPHER_ESSIV 130 
#define  DRV_CIPHER_OFB 129 
#define  DRV_CIPHER_XTS 128 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int S_DIN_to_AES ; 
 int /*<<< orphan*/  cc_key_type (struct crypto_tfm*) ; 
 int cc_out_flow_mode (struct cc_cipher_ctx*) ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_cpp_crypto_key (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_hw_crypto_key (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_key_size_des (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_setup_key_desc(struct crypto_tfm *tfm,
			      struct cipher_req_ctx *req_ctx,
			      unsigned int nbytes, struct cc_hw_desc desc[],
			      unsigned int *seq_size)
{
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx_p->drvdata);
	int cipher_mode = ctx_p->cipher_mode;
	int flow_mode = ctx_p->flow_mode;
	int direction = req_ctx->gen_ctx.op_type;
	dma_addr_t key_dma_addr = ctx_p->user.key_dma_addr;
	unsigned int key_len = ctx_p->keylen;
	unsigned int din_size;

	switch (cipher_mode) {
	case DRV_CIPHER_CBC:
	case DRV_CIPHER_CBC_CTS:
	case DRV_CIPHER_CTR:
	case DRV_CIPHER_OFB:
	case DRV_CIPHER_ECB:
		/* Load key */
		hw_desc_init(&desc[*seq_size]);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);

		if (cc_key_type(tfm) == CC_POLICY_PROTECTED_KEY) {
			/* We use the AES key size coding for all CPP algs */
			set_key_size_aes(&desc[*seq_size], key_len);
			set_cpp_crypto_key(&desc[*seq_size], ctx_p->cpp.slot);
			flow_mode = cc_out_flow_mode(ctx_p);
		} else {
			if (flow_mode == S_DIN_to_AES) {
				if (cc_key_type(tfm) == CC_HW_PROTECTED_KEY) {
					set_hw_crypto_key(&desc[*seq_size],
							  ctx_p->hw.key1_slot);
				} else {
					/* CC_POLICY_UNPROTECTED_KEY
					 * Invalid keys are filtered out in
					 * sethkey()
					 */
					din_size = (key_len == 24) ?
						AES_MAX_KEY_SIZE : key_len;

					set_din_type(&desc[*seq_size], DMA_DLLI,
						     key_dma_addr, din_size,
						     NS_BIT);
				}
				set_key_size_aes(&desc[*seq_size], key_len);
			} else {
				/*des*/
				set_din_type(&desc[*seq_size], DMA_DLLI,
					     key_dma_addr, key_len, NS_BIT);
				set_key_size_des(&desc[*seq_size], key_len);
			}
			set_setup_mode(&desc[*seq_size], SETUP_LOAD_KEY0);
		}
		set_flow_mode(&desc[*seq_size], flow_mode);
		(*seq_size)++;
		break;
	case DRV_CIPHER_XTS:
	case DRV_CIPHER_ESSIV:
	case DRV_CIPHER_BITLOCKER:
		/* Load AES key */
		hw_desc_init(&desc[*seq_size]);
		set_cipher_mode(&desc[*seq_size], cipher_mode);
		set_cipher_config0(&desc[*seq_size], direction);
		if (cc_key_type(tfm) == CC_HW_PROTECTED_KEY) {
			set_hw_crypto_key(&desc[*seq_size],
					  ctx_p->hw.key1_slot);
		} else {
			set_din_type(&desc[*seq_size], DMA_DLLI, key_dma_addr,
				     (key_len / 2), NS_BIT);
		}
		set_key_size_aes(&desc[*seq_size], (key_len / 2));
		set_flow_mode(&desc[*seq_size], flow_mode);
		set_setup_mode(&desc[*seq_size], SETUP_LOAD_KEY0);
		(*seq_size)++;
		break;
	default:
		dev_err(dev, "Unsupported cipher mode (%d)\n", cipher_mode);
	}
}