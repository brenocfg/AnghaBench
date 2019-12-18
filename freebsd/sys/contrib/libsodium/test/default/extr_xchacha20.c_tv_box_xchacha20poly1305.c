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
 scalar_t__ crypto_box_curve25519xchacha20poly1305_BEFORENMBYTES ; 
 size_t crypto_box_curve25519xchacha20poly1305_MACBYTES ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_MESSAGEBYTES_MAX ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_NONCEBYTES ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_PUBLICKEYBYTES ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_SECRETKEYBYTES ; 
 size_t crypto_box_curve25519xchacha20poly1305_SEEDBYTES ; 
 int crypto_box_curve25519xchacha20poly1305_beforenm (unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_beforenmbytes () ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_detached (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_detached_afternm (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_easy (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_easy_afternm (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_keypair (unsigned char*,unsigned char*) ; 
 size_t crypto_box_curve25519xchacha20poly1305_macbytes () ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_messagebytes_max () ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_noncebytes () ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_open_detached (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_open_detached_afternm (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 int crypto_box_curve25519xchacha20poly1305_open_easy (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*,unsigned char*) ; 
 int crypto_box_curve25519xchacha20poly1305_open_easy_afternm (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_publickeybytes () ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_secretkeybytes () ; 
 int /*<<< orphan*/  crypto_box_curve25519xchacha20poly1305_seed_keypair (unsigned char*,unsigned char*,unsigned char*) ; 
 size_t crypto_box_curve25519xchacha20poly1305_seedbytes () ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,size_t) ; 
 size_t randombytes_uniform (int) ; 
 unsigned char* small_order_p ; 
 int /*<<< orphan*/  sodium_bin2hex (char*,int,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
tv_box_xchacha20poly1305(void)
{
    char           hex[65];
    unsigned char *pk;
    unsigned char *sk;
    unsigned char *m;
    unsigned char *m2;
    unsigned char *mac;
    unsigned char *nonce;
    unsigned char *out;
    unsigned char *pc;
    unsigned char *seed;
    size_t         m_len;
    int            i;

    pk = (unsigned char *) sodium_malloc(crypto_box_curve25519xchacha20poly1305_PUBLICKEYBYTES);
    sk = (unsigned char *) sodium_malloc(crypto_box_curve25519xchacha20poly1305_SECRETKEYBYTES);
    nonce = (unsigned char *) sodium_malloc(crypto_box_curve25519xchacha20poly1305_NONCEBYTES);
    mac = (unsigned char *) sodium_malloc(crypto_box_curve25519xchacha20poly1305_MACBYTES);
    pc = (unsigned char *) sodium_malloc(crypto_box_curve25519xchacha20poly1305_BEFORENMBYTES);
    for (i = 0; i < 10; i++) {
        m_len = (i == 0) ? 0 : randombytes_uniform(150);
        m = (unsigned char *) sodium_malloc(m_len);
        m2 = (unsigned char *) sodium_malloc(m_len);

        out = (unsigned char *) sodium_malloc
            (crypto_box_curve25519xchacha20poly1305_MACBYTES + m_len);
        randombytes_buf(nonce, crypto_box_curve25519xchacha20poly1305_NONCEBYTES);
        randombytes_buf(m, m_len);
        assert(crypto_box_curve25519xchacha20poly1305_keypair(pk, sk) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_easy(out, m, 0, nonce,
                                                           pk, sk) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_easy(out, m, m_len, nonce,
                                                           pk, sk) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy
               (m2, out, crypto_box_curve25519xchacha20poly1305_MACBYTES + m_len,
                nonce, small_order_p, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy
               (m2, out, crypto_box_curve25519xchacha20poly1305_MACBYTES - 1,
                nonce, pk, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy
               (m2, out, 0, nonce, pk, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy
               (m2, out, crypto_box_curve25519xchacha20poly1305_MACBYTES + m_len,
                nonce, pk, sk) == 0);
        assert(memcmp(m2, m, m_len) == 0);
        sodium_free(out);

        out = (unsigned char *) sodium_malloc
            (crypto_box_curve25519xchacha20poly1305_MACBYTES + m_len);
        assert(crypto_box_curve25519xchacha20poly1305_beforenm(pc, small_order_p, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_beforenm(pc, pk, sk) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_easy_afternm
               (out, m, 0, nonce, pc) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_easy_afternm
               (out, m, m_len, nonce, pc) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy_afternm
               (m2, out, crypto_box_curve25519xchacha20poly1305_MACBYTES - 1,
                nonce, pc) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy_afternm
               (m2, out, 0,
                nonce, pc) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_easy_afternm
               (m2, out, crypto_box_curve25519xchacha20poly1305_MACBYTES + m_len,
                nonce, pc) == 0);
        assert(memcmp(m2, m, m_len) == 0);
        sodium_free(out);

        out = (unsigned char *) sodium_malloc(m_len);
        assert(crypto_box_curve25519xchacha20poly1305_detached(out, mac, m, m_len,
                                                               nonce, small_order_p, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_detached(out, mac, m, m_len,
                                                               nonce, pk, sk) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_open_detached
               (m2, out, mac, m_len, nonce, small_order_p, sk) == -1);
        assert(crypto_box_curve25519xchacha20poly1305_open_detached
               (m2, out, mac, m_len, nonce, pk, sk) == 0);
        sodium_free(out);

        out = (unsigned char *) sodium_malloc(m_len);
        assert(crypto_box_curve25519xchacha20poly1305_detached_afternm
               (out, mac, m, m_len, nonce, pc) == 0);
        assert(crypto_box_curve25519xchacha20poly1305_open_detached_afternm
               (m2, out, mac, m_len, nonce, pc) == 0);
        sodium_free(out);

        sodium_free(m2);
        sodium_free(m);
    }
    sodium_free(pc);
    sodium_free(mac);
    sodium_free(nonce);

    seed = (unsigned char *) sodium_malloc
        (crypto_box_curve25519xchacha20poly1305_SEEDBYTES);
    for (i = 0; i <(int)  crypto_box_curve25519xchacha20poly1305_SEEDBYTES; i++) {
        seed[i] = (unsigned char) i;
    }
    crypto_box_curve25519xchacha20poly1305_seed_keypair(pk, sk, seed);
    sodium_bin2hex(hex, sizeof hex, pk, crypto_box_curve25519xchacha20poly1305_PUBLICKEYBYTES);
    assert(strcmp(hex, "4701d08488451f545a409fb58ae3e58581ca40ac3f7f114698cd71deac73ca01") == 0);
    sodium_bin2hex(hex, sizeof hex, sk, crypto_box_curve25519xchacha20poly1305_SECRETKEYBYTES);
    assert(strcmp(hex, "3d94eea49c580aef816935762be049559d6d1440dede12e6a125f1841fff8e6f") == 0);
    sodium_free(seed);

    sodium_free(sk);
    sodium_free(pk);

    assert(crypto_box_curve25519xchacha20poly1305_seedbytes() == crypto_box_curve25519xchacha20poly1305_SEEDBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_publickeybytes() == crypto_box_curve25519xchacha20poly1305_PUBLICKEYBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_secretkeybytes() == crypto_box_curve25519xchacha20poly1305_SECRETKEYBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_beforenmbytes() == crypto_box_curve25519xchacha20poly1305_BEFORENMBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_noncebytes() == crypto_box_curve25519xchacha20poly1305_NONCEBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_macbytes() == crypto_box_curve25519xchacha20poly1305_MACBYTES);
    assert(crypto_box_curve25519xchacha20poly1305_messagebytes_max() == crypto_box_curve25519xchacha20poly1305_MESSAGEBYTES_MAX);

    printf("tv_box_xchacha20poly1305: ok\n");
}