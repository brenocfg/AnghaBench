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
struct cc_hw_desc {int dummy; } ;
struct TYPE_3__ {scalar_t__ xcbc_keys_dma_addr; } ;
struct TYPE_4__ {TYPE_1__ xcbc; } ;
struct cc_aead_ctx {TYPE_2__ auth_state; int /*<<< orphan*/  auth_keylen; } ;

/* Variables and functions */
 int AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  CC_AES_128_BIT_KEY_SIZE ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_ECB ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int xcbc_setkey(struct cc_hw_desc *desc,
				struct cc_aead_ctx *ctx)
{
	/* Load the AES key */
	hw_desc_init(&desc[0]);
	/* We are using for the source/user key the same buffer
	 * as for the output keys, * because after this key loading it
	 * is not needed anymore
	 */
	set_din_type(&desc[0], DMA_DLLI,
		     ctx->auth_state.xcbc.xcbc_keys_dma_addr, ctx->auth_keylen,
		     NS_BIT);
	set_cipher_mode(&desc[0], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[0], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_key_size_aes(&desc[0], ctx->auth_keylen);
	set_flow_mode(&desc[0], S_DIN_to_AES);
	set_setup_mode(&desc[0], SETUP_LOAD_KEY0);

	hw_desc_init(&desc[1]);
	set_din_const(&desc[1], 0x01010101, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[1], DIN_AES_DOUT);
	set_dout_dlli(&desc[1], ctx->auth_state.xcbc.xcbc_keys_dma_addr,
		      AES_KEYSIZE_128, NS_BIT, 0);

	hw_desc_init(&desc[2]);
	set_din_const(&desc[2], 0x02020202, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[2], DIN_AES_DOUT);
	set_dout_dlli(&desc[2], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					 + AES_KEYSIZE_128),
			      AES_KEYSIZE_128, NS_BIT, 0);

	hw_desc_init(&desc[3]);
	set_din_const(&desc[3], 0x03030303, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[3], DIN_AES_DOUT);
	set_dout_dlli(&desc[3], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					  + 2 * AES_KEYSIZE_128),
			      AES_KEYSIZE_128, NS_BIT, 0);

	return 4;
}