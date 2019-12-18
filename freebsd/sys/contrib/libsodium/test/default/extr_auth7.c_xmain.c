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
 int* a ; 
 int* c ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512 (int*,int*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_auth_hmacsha512_verify (int*,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_auth_keygen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int rand () ; 
 int /*<<< orphan*/  randombytes_buf (int*,size_t) ; 

int
main(void)
{
    size_t clen;

    for (clen = 0; clen < sizeof c; ++clen) {
        crypto_auth_keygen(key);
        randombytes_buf(c, clen);
        crypto_auth_hmacsha512(a, c, clen, key);
        if (crypto_auth_hmacsha512_verify(a, c, clen, key) != 0) {
            printf("fail %u\n", (unsigned int) clen);
            return 100;
        }
        if (clen > 0) {
            c[(size_t) rand() % clen] += 1 + (rand() % 255);
            if (crypto_auth_hmacsha512_verify(a, c, clen, key) == 0) {
                printf("forgery %u\n", (unsigned int) clen);
                return 100;
            }
            a[rand() % sizeof a] += 1 + (rand() % 255);
            if (crypto_auth_hmacsha512_verify(a, c, clen, key) == 0) {
                printf("forgery %u\n", (unsigned int) clen);
                return 100;
            }
        }
    }
    return 0;
}