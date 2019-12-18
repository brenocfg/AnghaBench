#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_5__ {size_t blocksz; } ;
typedef  TYPE_1__ cf_prp ;
typedef  int /*<<< orphan*/  cf_ctr ;
typedef  int /*<<< orphan*/  cf_cbcmac_stream ;

/* Variables and functions */
 int CF_MAXBLOCK ; 
 int /*<<< orphan*/  add_aad (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  add_block0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  build_ctr_nonce (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_init (int /*<<< orphan*/ *,TYPE_1__ const*,void*) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_nopad_final (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_cbcmac_stream_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cf_ctr_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  cf_ctr_custom_counter (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  cf_ctr_init (int /*<<< orphan*/ *,TYPE_1__ const*,void*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  zero_pad (int /*<<< orphan*/ *) ; 

void cf_ccm_encrypt(const cf_prp *prp, void *prpctx,
                    const uint8_t *plain, size_t nplain, size_t L,
                    const uint8_t *header, size_t nheader,
                    const uint8_t *nonce, size_t nnonce,
                    uint8_t *cipher,
                    uint8_t *tag, size_t ntag)
{
  uint8_t block[CF_MAXBLOCK];

  assert(ntag >= 4 && ntag <= 16 && ntag % 2 == 0);
  assert(L >= 2 && L <= 8);
  assert(nnonce == prp->blocksz - L - 1);

  cf_cbcmac_stream cm;
  cf_cbcmac_stream_init(&cm, prp, prpctx);

  /* Add first block. */
  add_block0(&cm, block, prp->blocksz,
             nonce, nnonce,
             L, nplain, nheader, ntag);

  /* Add AAD with length prefix, if present. */
  if (nheader)
    add_aad(&cm, block, header, nheader);

  /* Add message. */
  cf_cbcmac_stream_update(&cm, plain, nplain);
  zero_pad(&cm);

  /* Finish tag. */
  cf_cbcmac_stream_nopad_final(&cm, block);

  /* Start encryption. */
  /* Construct A_0 */
  uint8_t ctr_nonce[CF_MAXBLOCK];
  build_ctr_nonce(ctr_nonce, L, nonce, nnonce);

  cf_ctr ctr;
  cf_ctr_init(&ctr, prp, prpctx, ctr_nonce);
  cf_ctr_custom_counter(&ctr, prp->blocksz - L, L);

  /* Encrypt tag first. */
  cf_ctr_cipher(&ctr, block, block, prp->blocksz);
  memcpy(tag, block, ntag);

  /* Then encrypt message. */
  cf_ctr_cipher(&ctr, plain, cipher, nplain);
}