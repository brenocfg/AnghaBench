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
struct TYPE_2__ {char* outcome; int /*<<< orphan*/  detached_ciphertext_hex; int /*<<< orphan*/  mac_hex; int /*<<< orphan*/  ad_hex; int /*<<< orphan*/  message_hex; int /*<<< orphan*/  nonce_hex; int /*<<< orphan*/  key_hex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int crypto_aead_chacha20poly1305_ietf_ABYTES ; 
 int crypto_aead_chacha20poly1305_ietf_KEYBYTES ; 
 int crypto_aead_chacha20poly1305_ietf_NPUBBYTES ; 
 scalar_t__ crypto_aead_chacha20poly1305_ietf_decrypt_detached (unsigned char*,int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,...) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 int /*<<< orphan*/  sodium_hex2bin (unsigned char*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_malloc (size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* tests ; 

__attribute__((used)) static int
tv(void)
{
    unsigned char *ad;
    unsigned char *decrypted;
    unsigned char *detached_ciphertext;
    unsigned char *key;
    unsigned char *message;
    unsigned char *mac;
    unsigned char *nonce;
    size_t         ad_len;
    size_t         detached_ciphertext_len;
    size_t         message_len;
    unsigned int   i;

    key = (unsigned char *) sodium_malloc(
        crypto_aead_chacha20poly1305_ietf_KEYBYTES);
    nonce = (unsigned char *) sodium_malloc(
        crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
    mac = (unsigned char *) sodium_malloc(
        crypto_aead_chacha20poly1305_ietf_ABYTES);

    for (i = 0U; i < (sizeof tests) / (sizeof tests[0]); i++) {
        assert(strlen(tests[i].key_hex) ==
               2 * crypto_aead_chacha20poly1305_ietf_KEYBYTES);
        sodium_hex2bin(key, crypto_aead_chacha20poly1305_ietf_KEYBYTES,
                       tests[i].key_hex, strlen(tests[i].key_hex), NULL, NULL,
                       NULL);

        assert(strlen(tests[i].nonce_hex) ==
               2 * crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
        sodium_hex2bin(nonce, crypto_aead_chacha20poly1305_ietf_NPUBBYTES,
                       tests[i].nonce_hex, strlen(tests[i].nonce_hex), NULL,
                       NULL, NULL);

        message_len = strlen(tests[i].message_hex) / 2;
        message     = (unsigned char *) sodium_malloc(message_len);
        sodium_hex2bin(message, message_len, tests[i].message_hex,
                       strlen(tests[i].message_hex), NULL, NULL, NULL);

        ad_len = strlen(tests[i].ad_hex) / 2;
        ad     = (unsigned char *) sodium_malloc(ad_len);
        sodium_hex2bin(ad, ad_len, tests[i].ad_hex, strlen(tests[i].ad_hex),
                       NULL, NULL, NULL);

        detached_ciphertext_len = message_len;
        assert(strlen(tests[i].detached_ciphertext_hex) == 2 * message_len);
        assert(strlen(tests[i].mac_hex) ==
               2 * crypto_aead_chacha20poly1305_ietf_ABYTES);
        sodium_hex2bin(mac, crypto_aead_chacha20poly1305_ietf_ABYTES,
                       tests[i].mac_hex, strlen(tests[i].mac_hex), NULL, NULL,
                       NULL);

        detached_ciphertext =
            (unsigned char *) sodium_malloc(detached_ciphertext_len);
        sodium_hex2bin(detached_ciphertext, detached_ciphertext_len,
                       tests[i].detached_ciphertext_hex,
                       strlen(tests[i].detached_ciphertext_hex), NULL, NULL,
                       NULL);

        decrypted = (unsigned char *) sodium_malloc(message_len);
        if (crypto_aead_chacha20poly1305_ietf_decrypt_detached(
                decrypted, NULL, detached_ciphertext, detached_ciphertext_len,
                mac, ad, ad_len, nonce, key) == 0) {
            if (strcmp(tests[i].outcome, "valid") != 0) {
                printf("*** test case %u succeeded, was supposed to be %s\n", i,
                       tests[i].outcome);
            }
            if (memcmp(decrypted, message, message_len) != 0) {
                printf("Incorrect decryption of test vector #%u\n",
                       (unsigned int) i);
            }
        } else {
            if (strcmp(tests[i].outcome, "invalid") != 0) {
                printf("*** test case %u failed, was supposed to be %s\n", i,
                       tests[i].outcome);
            }
        }

        sodium_free(message);
        sodium_free(ad);
        sodium_free(decrypted);
        sodium_free(detached_ciphertext);
    }

    sodium_free(key);
    sodium_free(mac);
    sodium_free(nonce);

    return 0;
}