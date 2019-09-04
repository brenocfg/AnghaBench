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
 int /*<<< orphan*/  assert (int) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 size_t crypto_box_SEALBYTES ; 
 int crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_seal (unsigned char*,unsigned char*,size_t,unsigned char*) ; 
 int crypto_box_seal_open (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 size_t crypto_box_sealbytes () ; 
 int memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,size_t) ; 
 scalar_t__ randombytes_uniform (int) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (size_t) ; 

__attribute__((used)) static
void tv1(void)
{
    unsigned char  pk[crypto_box_PUBLICKEYBYTES];
    unsigned char  sk[crypto_box_SECRETKEYBYTES];
    unsigned char *c;
    unsigned char *m;
    unsigned char *m2;
    size_t         m_len;
    size_t         c_len;

    crypto_box_keypair(pk, sk);
    m_len = (size_t) randombytes_uniform(1000);
    c_len = crypto_box_SEALBYTES + m_len;
    m     = (unsigned char *) sodium_malloc(m_len);
    m2    = (unsigned char *) sodium_malloc(m_len);
    c     = (unsigned char *) sodium_malloc(c_len);
    randombytes_buf(m, m_len);
    if (crypto_box_seal(c, m, m_len, pk) != 0) {
        printf("crypto_box_seal() failure\n");
        return;
    }
    if (crypto_box_seal_open(m2, c, c_len, pk, sk) != 0) {
        printf("crypto_box_seal_open() failure\n");
        return;
    }
    printf("%d\n", memcmp(m, m2, m_len));

    printf("%d\n", crypto_box_seal_open(m, c, 0U, pk, sk));
    printf("%d\n", crypto_box_seal_open(m, c, c_len - 1U, pk, sk));
    printf("%d\n", crypto_box_seal_open(m, c, c_len, sk, pk));

    sodium_free(c);
    sodium_free(m);
    sodium_free(m2);

    assert(crypto_box_sealbytes() == crypto_box_SEALBYTES);
}