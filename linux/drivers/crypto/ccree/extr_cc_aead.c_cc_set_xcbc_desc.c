#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_3__ {scalar_t__ xcbc_keys_dma_addr; } ;
struct TYPE_4__ {TYPE_1__ xcbc; } ;
struct cc_aead_ctx {TYPE_2__ auth_state; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  CC_AES_128_BIT_KEY_SIZE ; 
 int /*<<< orphan*/  CC_AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DESC_DIRECTION_ENCRYPT_ENCRYPT ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_XCBC_MAC ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE2 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_aes_not_hash_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_xcbc_desc(struct aead_request *req, struct cc_hw_desc desc[],
			     unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	unsigned int idx = *seq_size;

	/* Loading MAC state */
	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0, CC_AES_BLOCK_SIZE);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K1 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     ctx->auth_state.xcbc.xcbc_keys_dma_addr,
		     AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K2 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.xcbc.xcbc_keys_dma_addr +
		      AES_KEYSIZE_128), AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K3 */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.xcbc.xcbc_keys_dma_addr +
		      2 * AES_KEYSIZE_128), AES_KEYSIZE_128, NS_BIT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE2);
	set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_key_size_aes(&desc[idx], CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	*seq_size = idx;
}