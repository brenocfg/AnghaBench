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

__attribute__((used)) static unsigned int blob_length(unsigned bitlen, int isdss, int ispub)
{
    unsigned int nbyte, hnbyte;
    nbyte = (bitlen + 7) >> 3;
    hnbyte = (bitlen + 15) >> 4;
    if (isdss) {

        /*
         * Expected length: 20 for q + 3 components bitlen each + 24 for seed
         * structure.
         */
        if (ispub)
            return 44 + 3 * nbyte;
        /*
         * Expected length: 20 for q, priv, 2 bitlen components + 24 for seed
         * structure.
         */
        else
            return 64 + 2 * nbyte;
    } else {
        /* Expected length: 4 for 'e' + 'n' */
        if (ispub)
            return 4 + nbyte;
        else
            /*
             * Expected length: 4 for 'e' and 7 other components. 2
             * components are bitlen size, 5 are bitlen/2
             */
            return 4 + 2 * nbyte + 5 * hnbyte;
    }

}