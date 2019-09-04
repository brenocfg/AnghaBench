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
 int /*<<< orphan*/  alicepk_ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bobsk_ ; 
 int crypto_scalarmult (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_scalarmult_BYTES ; 
 int /*<<< orphan*/  crypto_scalarmult_SCALARBYTES ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (int /*<<< orphan*/ ) ; 

int
main(void)
{
    unsigned char *k;
    unsigned char *bobsk;
    unsigned char *alicepk;
    int            i;
    int            ret;

    k       = (unsigned char *) sodium_malloc(crypto_scalarmult_BYTES);
    bobsk   = (unsigned char *) sodium_malloc(crypto_scalarmult_SCALARBYTES);
    alicepk = (unsigned char *) sodium_malloc(crypto_scalarmult_SCALARBYTES);
    assert(k != NULL && bobsk != NULL && alicepk != NULL);

    memcpy(bobsk, bobsk_, crypto_scalarmult_SCALARBYTES);
    memcpy(alicepk, alicepk_, crypto_scalarmult_SCALARBYTES);

    ret = crypto_scalarmult(k, bobsk, alicepk);
    assert(ret == 0);

    sodium_free(alicepk);
    sodium_free(bobsk);

    for (i = 0; i < 32; ++i) {
        if (i > 0) {
            printf(",");
        } else {
            printf(" ");
        }
        printf("0x%02x", (unsigned int) k[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    sodium_free(k);

    return 0;
}