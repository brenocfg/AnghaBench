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
 int crypto_secretbox_MACBYTES ; 
 int /*<<< orphan*/  crypto_secretbox_detached (unsigned char*,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_secretbox_easy (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_secretbox_open_easy (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstkey ; 
 unsigned char* m ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t randombytes_uniform (int) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (int) ; 

int
main(void)
{
    unsigned char *c;
    unsigned char *mac;
    size_t         i;

    c   = (unsigned char *) sodium_malloc(131 + crypto_secretbox_MACBYTES + 1);
    mac = (unsigned char *) sodium_malloc(crypto_secretbox_MACBYTES);
    assert(c != NULL && mac != NULL);

    crypto_secretbox_easy(c, m, 131, nonce, firstkey);
    for (i = 0; i < 131 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    crypto_secretbox_detached(c, mac, m, 131, nonce, firstkey);
    for (i = 0; i < crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) mac[i]);
    }
    for (i = 0; i < 131; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    /* Same test, with c and m overlapping */

    memcpy(c + 1, m, 131);
    crypto_secretbox_easy(c, c + 1, 131, nonce, firstkey);
    for (i = 0; i < 131 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    memcpy(c, m, 131);
    crypto_secretbox_easy(c + 1, c, 131, nonce, firstkey);
    for (i = 0; i < 131 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i + 1]);
    }
    printf("\n");

    memcpy(c, m, 131);
    crypto_secretbox_easy(c, c, 131, nonce, firstkey);
    for (i = 0; i < 131 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    assert(crypto_secretbox_easy(c, m, 0, nonce, firstkey) == 0);

    /* Null message */

    crypto_secretbox_easy(c, c, 0, nonce, firstkey);
    for (i = 0; i < crypto_secretbox_MACBYTES + 1; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");
    if (crypto_secretbox_open_easy(c, c, crypto_secretbox_MACBYTES, nonce,
                                   firstkey) != 0) {
        printf("Null crypto_secretbox_open_easy() failed\n");
    }
    for (i = 0; i < crypto_secretbox_MACBYTES + 1; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");
    c[randombytes_uniform(crypto_secretbox_MACBYTES)]++;
    if (crypto_secretbox_open_easy(c, c, crypto_secretbox_MACBYTES, nonce,
                                   firstkey) != -1) {
        printf("Null tampered crypto_secretbox_open_easy() failed\n");
    }

    /* No overlap, but buffers are next to each other */

    memset(c, 0, 131 + crypto_secretbox_MACBYTES + 1);
    memcpy(c, m, 20);
    crypto_secretbox_easy(c, c + 10, 10, nonce, firstkey);
    for (i = 0; i < 10 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    memset(c, 0, 131 + crypto_secretbox_MACBYTES + 1);
    memcpy(c, m, 20);
    crypto_secretbox_easy(c + 10, c, 10, nonce, firstkey);
    for (i = 0; i < 10 + crypto_secretbox_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    sodium_free(mac);
    sodium_free(c);

    return 0;
}