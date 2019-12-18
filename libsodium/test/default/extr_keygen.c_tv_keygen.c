#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int key_len; int /*<<< orphan*/  (* fn ) (unsigned char*) ;int /*<<< orphan*/  const member_1; int /*<<< orphan*/  const member_0; } ;
typedef  TYPE_1__ KeygenTV ;

/* Variables and functions */
#define  crypto_aead_aes256gcm_KEYBYTES 171 
#define  crypto_aead_aes256gcm_keygen 170 
#define  crypto_aead_chacha20poly1305_KEYBYTES 169 
#define  crypto_aead_chacha20poly1305_ietf_KEYBYTES 168 
#define  crypto_aead_chacha20poly1305_ietf_keygen 167 
#define  crypto_aead_chacha20poly1305_keygen 166 
#define  crypto_aead_xchacha20poly1305_ietf_KEYBYTES 165 
#define  crypto_aead_xchacha20poly1305_ietf_keygen 164 
#define  crypto_auth_KEYBYTES 163 
#define  crypto_auth_hmacsha256_KEYBYTES 162 
#define  crypto_auth_hmacsha256_keygen 161 
#define  crypto_auth_hmacsha512256_KEYBYTES 160 
#define  crypto_auth_hmacsha512256_keygen 159 
#define  crypto_auth_hmacsha512_KEYBYTES 158 
#define  crypto_auth_hmacsha512_keygen 157 
#define  crypto_auth_keygen 156 
#define  crypto_generichash_KEYBYTES 155 
#define  crypto_generichash_blake2b_KEYBYTES 154 
#define  crypto_generichash_blake2b_keygen 153 
#define  crypto_generichash_keygen 152 
#define  crypto_kdf_KEYBYTES 151 
#define  crypto_kdf_keygen 150 
#define  crypto_onetimeauth_KEYBYTES 149 
#define  crypto_onetimeauth_keygen 148 
#define  crypto_onetimeauth_poly1305_KEYBYTES 147 
#define  crypto_onetimeauth_poly1305_keygen 146 
#define  crypto_secretbox_KEYBYTES 145 
#define  crypto_secretbox_keygen 144 
#define  crypto_secretbox_xsalsa20poly1305_KEYBYTES 143 
#define  crypto_secretbox_xsalsa20poly1305_keygen 142 
#define  crypto_secretstream_xchacha20poly1305_KEYBYTES 141 
#define  crypto_secretstream_xchacha20poly1305_keygen 140 
#define  crypto_shorthash_KEYBYTES 139 
#define  crypto_shorthash_keygen 138 
#define  crypto_stream_KEYBYTES 137 
#define  crypto_stream_chacha20_KEYBYTES 136 
#define  crypto_stream_chacha20_ietf_KEYBYTES 135 
#define  crypto_stream_chacha20_ietf_keygen 134 
#define  crypto_stream_chacha20_keygen 133 
#define  crypto_stream_keygen 132 
#define  crypto_stream_salsa20_KEYBYTES 131 
#define  crypto_stream_salsa20_keygen 130 
#define  crypto_stream_xsalsa20_KEYBYTES 129 
#define  crypto_stream_xsalsa20_keygen 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*) ; 

__attribute__((used)) static void
tv_keygen(void)
{
    static const KeygenTV tvs[] = {
        { crypto_auth_keygen, crypto_auth_KEYBYTES },
        { crypto_auth_hmacsha256_keygen, crypto_auth_hmacsha256_KEYBYTES },
        { crypto_aead_aes256gcm_keygen, crypto_aead_aes256gcm_KEYBYTES },
        { crypto_auth_hmacsha512_keygen, crypto_auth_hmacsha512_KEYBYTES },
        { crypto_auth_hmacsha512256_keygen, crypto_auth_hmacsha512256_KEYBYTES },
        { crypto_generichash_keygen, crypto_generichash_KEYBYTES },
        { crypto_generichash_blake2b_keygen, crypto_generichash_blake2b_KEYBYTES },
        { crypto_kdf_keygen, crypto_kdf_KEYBYTES },
        { crypto_onetimeauth_keygen, crypto_onetimeauth_KEYBYTES },
        { crypto_onetimeauth_poly1305_keygen, crypto_onetimeauth_poly1305_KEYBYTES },
        { crypto_aead_chacha20poly1305_ietf_keygen, crypto_aead_chacha20poly1305_ietf_KEYBYTES },
        { crypto_aead_chacha20poly1305_keygen, crypto_aead_chacha20poly1305_KEYBYTES },
        { crypto_aead_chacha20poly1305_ietf_keygen, crypto_aead_chacha20poly1305_ietf_KEYBYTES },
        { crypto_aead_xchacha20poly1305_ietf_keygen, crypto_aead_xchacha20poly1305_ietf_KEYBYTES },
        { crypto_secretbox_xsalsa20poly1305_keygen, crypto_secretbox_xsalsa20poly1305_KEYBYTES },
        { crypto_secretbox_keygen, crypto_secretbox_KEYBYTES },
        { crypto_secretstream_xchacha20poly1305_keygen, crypto_secretstream_xchacha20poly1305_KEYBYTES },
        { crypto_shorthash_keygen, crypto_shorthash_KEYBYTES },
        { crypto_stream_keygen, crypto_stream_KEYBYTES },
        { crypto_stream_chacha20_keygen, crypto_stream_chacha20_KEYBYTES },
        { crypto_stream_chacha20_ietf_keygen, crypto_stream_chacha20_ietf_KEYBYTES },
        { crypto_stream_salsa20_keygen, crypto_stream_salsa20_KEYBYTES },
        { crypto_stream_xsalsa20_keygen, crypto_stream_xsalsa20_KEYBYTES }
    };
    const KeygenTV *tv;
    unsigned char  *key;
    size_t          i;
    int             j;

    for (i = 0; i < (sizeof tvs) / (sizeof tvs[0]); i++) {
        tv = &tvs[i];
        key = (unsigned char *) sodium_malloc(tv->key_len);
        key[tv->key_len - 1U] = 0;
        for (j = 0; j < 10000; j++) {
            tv->fn(key);
            if (key[tv->key_len - 1U] != 0) {
                break;
            }
        }
        sodium_free(key);
        if (j >= 10000) {
            printf("Buffer underflow with test vector %u\n", (unsigned int) i);
        }
    }
    printf("tv_keygen: ok\n");
}