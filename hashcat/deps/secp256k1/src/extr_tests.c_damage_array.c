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

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int secp256k1_rand_bits (int) ; 
 size_t secp256k1_rand_int (size_t) ; 

__attribute__((used)) static void damage_array(unsigned char *sig, size_t *len) {
    int pos;
    int action = secp256k1_rand_bits(3);
    if (action < 1 && *len > 3) {
        /* Delete a byte. */
        pos = secp256k1_rand_int(*len);
        memmove(sig + pos, sig + pos + 1, *len - pos - 1);
        (*len)--;
        return;
    } else if (action < 2 && *len < 2048) {
        /* Insert a byte. */
        pos = secp256k1_rand_int(1 + *len);
        memmove(sig + pos + 1, sig + pos, *len - pos);
        sig[pos] = secp256k1_rand_bits(8);
        (*len)++;
        return;
    } else if (action < 4) {
        /* Modify a byte. */
        sig[secp256k1_rand_int(*len)] += 1 + secp256k1_rand_int(255);
        return;
    } else { /* action < 8 */
        /* Modify a bit. */
        sig[secp256k1_rand_int(*len)] ^= 1 << secp256k1_rand_bits(3);
        return;
    }
}