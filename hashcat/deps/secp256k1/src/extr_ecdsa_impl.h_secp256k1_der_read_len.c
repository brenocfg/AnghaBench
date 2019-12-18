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
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int secp256k1_der_read_len(size_t *len, const unsigned char **sigp, const unsigned char *sigend) {
    size_t lenleft;
    unsigned char b1;
    VERIFY_CHECK(len != NULL);
    *len = 0;
    if (*sigp >= sigend) {
        return 0;
    }
    b1 = *((*sigp)++);
    if (b1 == 0xFF) {
        /* X.690-0207 8.1.3.5.c the value 0xFF shall not be used. */
        return 0;
    }
    if ((b1 & 0x80) == 0) {
        /* X.690-0207 8.1.3.4 short form length octets */
        *len = b1;
        return 1;
    }
    if (b1 == 0x80) {
        /* Indefinite length is not allowed in DER. */
        return 0;
    }
    /* X.690-207 8.1.3.5 long form length octets */
    lenleft = b1 & 0x7F; /* lenleft is at least 1 */
    if (lenleft > (size_t)(sigend - *sigp)) {
        return 0;
    }
    if (**sigp == 0) {
        /* Not the shortest possible length encoding. */
        return 0;
    }
    if (lenleft > sizeof(size_t)) {
        /* The resulting length would exceed the range of a size_t, so
         * certainly longer than the passed array size.
         */
        return 0;
    }
    while (lenleft > 0) {
        *len = (*len << 8) | **sigp;
        (*sigp)++;
        lenleft--;
    }
    if (*len > (size_t)(sigend - *sigp)) {
        /* Result exceeds the length of the passed array. */
        return 0;
    }
    if (*len < 128) {
        /* Not the shortest possible length encoding. */
        return 0;
    }
    return 1;
}