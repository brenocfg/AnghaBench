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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct cryptodesc {int crd_len; } ;

/* Variables and functions */
 int CCM_B0_SIZE ; 
 int CCM_CBC_BLOCK_LEN ; 
 int /*<<< orphan*/  htobe16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static void
generate_ccm_b0(struct cryptodesc *crda, struct cryptodesc *crde,
    u_int hash_size_in_response, const char *iv, char *b0)
{
	u_int i, payload_len;

	/* NB: L is already set in the first byte of the IV. */
	memcpy(b0, iv, CCM_B0_SIZE);

	/* Set length of hash in bits 3 - 5. */
	b0[0] |= (((hash_size_in_response - 2) / 2) << 3);

	/* Store the payload length as a big-endian value. */
	payload_len = crde->crd_len;
	for (i = 0; i < iv[0]; i++) {
		b0[CCM_CBC_BLOCK_LEN - 1 - i] = payload_len;
		payload_len >>= 8;
	}

	/*
	 * If there is AAD in the request, set bit 6 in the flags
	 * field and store the AAD length as a big-endian value at the
	 * start of block 1.  This only assumes a 16-bit AAD length
	 * since T6 doesn't support large AAD sizes.
	 */
	if (crda->crd_len != 0) {
		b0[0] |= (1 << 6);
		*(uint16_t *)(b0 + CCM_B0_SIZE) = htobe16(crda->crd_len);
	}
}