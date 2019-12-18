#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cache; int /*<<< orphan*/  prf_key; scalar_t__ nonce; } ;
typedef  TYPE_1__ pdf_ctx ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int const LOW_BIT_MASK ; 
 int /*<<< orphan*/  aes_encryption (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdf_gen_xor(pdf_ctx *pc, const UINT8 nonce[8], UINT8 buf[8])
{
    /* 'ndx' indicates that we'll be using the 0th or 1st eight bytes
     * of the AES output. If last time around we returned the ndx-1st
     * element, then we may have the result in the cache already.
     */

#if (UMAC_OUTPUT_LEN == 4)
#define LOW_BIT_MASK 3
#elif (UMAC_OUTPUT_LEN == 8)
#define LOW_BIT_MASK 1
#elif (UMAC_OUTPUT_LEN > 8)
#define LOW_BIT_MASK 0
#endif
    union {
        UINT8 tmp_nonce_lo[4];
        UINT32 align;
    } t;
#if LOW_BIT_MASK != 0
    int ndx = nonce[7] & LOW_BIT_MASK;
#endif
    *(UINT32 *)t.tmp_nonce_lo = ((const UINT32 *)nonce)[1];
    t.tmp_nonce_lo[3] &= ~LOW_BIT_MASK; /* zero last bit */

    if ( (((UINT32 *)t.tmp_nonce_lo)[0] != ((UINT32 *)pc->nonce)[1]) ||
         (((const UINT32 *)nonce)[0] != ((UINT32 *)pc->nonce)[0]) )
    {
        ((UINT32 *)pc->nonce)[0] = ((const UINT32 *)nonce)[0];
        ((UINT32 *)pc->nonce)[1] = ((UINT32 *)t.tmp_nonce_lo)[0];
        aes_encryption(pc->nonce, pc->cache, pc->prf_key);
    }

#if (UMAC_OUTPUT_LEN == 4)
    *((UINT32 *)buf) ^= ((UINT32 *)pc->cache)[ndx];
#elif (UMAC_OUTPUT_LEN == 8)
    *((UINT64 *)buf) ^= ((UINT64 *)pc->cache)[ndx];
#elif (UMAC_OUTPUT_LEN == 12)
    ((UINT64 *)buf)[0] ^= ((UINT64 *)pc->cache)[0];
    ((UINT32 *)buf)[2] ^= ((UINT32 *)pc->cache)[2];
#elif (UMAC_OUTPUT_LEN == 16)
    ((UINT64 *)buf)[0] ^= ((UINT64 *)pc->cache)[0];
    ((UINT64 *)buf)[1] ^= ((UINT64 *)pc->cache)[1];
#endif
}