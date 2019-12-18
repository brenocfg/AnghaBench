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
typedef  int u8 ;
struct cc_hw_desc {int /*<<< orphan*/ * word; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CPP_DIN_ADDR ; 
 int CC_CPP_DIN_SIZE ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD1_DIN_SIZE ; 
 int /*<<< orphan*/  WORD1_LOCK_QUEUE ; 
 int /*<<< orphan*/  WORD4_SETUP_OPERATION ; 

__attribute__((used)) static inline void set_cpp_crypto_key(struct cc_hw_desc *pdesc, u8 slot)
{
	pdesc->word[0] |= CC_CPP_DIN_ADDR;

	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_SIZE, CC_CPP_DIN_SIZE);
	pdesc->word[1] |= FIELD_PREP(WORD1_LOCK_QUEUE, 1);

	pdesc->word[4] |= FIELD_PREP(WORD4_SETUP_OPERATION, slot);
}