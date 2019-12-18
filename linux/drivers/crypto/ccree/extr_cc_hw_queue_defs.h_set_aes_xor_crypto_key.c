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
struct cc_hw_desc {int /*<<< orphan*/ * word; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD4_AES_XOR_CRYPTO_KEY ; 

__attribute__((used)) static inline void set_aes_xor_crypto_key(struct cc_hw_desc *pdesc)
{
	pdesc->word[4] |= FIELD_PREP(WORD4_AES_XOR_CRYPTO_KEY, 1);
}