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
 int EINVAL ; 
 int MEMLIMIT ; 
 int OPSLIMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_pwhash_ALG_ARGON2I13 ; 
 int /*<<< orphan*/  crypto_pwhash_ALG_ARGON2ID13 ; 
 scalar_t__ crypto_pwhash_STRBYTES ; 
 int crypto_pwhash_argon2i_str_needs_rehash (char*,int,int) ; 
 scalar_t__ crypto_pwhash_argon2i_str_verify (char*,char*,int) ; 
 unsigned int crypto_pwhash_argon2id_SALTBYTES ; 
 unsigned int crypto_pwhash_argon2id_STRBYTES ; 
 int crypto_pwhash_argon2id_str_needs_rehash (char*,int,int) ; 
 scalar_t__ crypto_pwhash_argon2id_str_verify (char*,char const*,int) ; 
 int crypto_pwhash_str (char*,char const*,int,int,int) ; 
 scalar_t__ crypto_pwhash_str_alg (char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int crypto_pwhash_str_needs_rehash (char*,int,int) ; 
 int crypto_pwhash_str_verify (char*,char const*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_free (char*) ; 
 int sodium_is_zero (unsigned char const*,scalar_t__) ; 
 scalar_t__ sodium_malloc (unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
str_tests(void)
{
    char       *str_out;
    char       *str_out2;
    char       *salt;
    const char *passwd = "Correct Horse Battery Staple";

    salt     = (char *) sodium_malloc(crypto_pwhash_argon2id_SALTBYTES);
    str_out  = (char *) sodium_malloc(crypto_pwhash_argon2id_STRBYTES);
    str_out2 = (char *) sodium_malloc(crypto_pwhash_argon2id_STRBYTES);
    memcpy(salt, ">A 16-bytes salt", crypto_pwhash_argon2id_SALTBYTES);
    if (crypto_pwhash_str(str_out, passwd, strlen(passwd), OPSLIMIT,
                          MEMLIMIT) != 0) {
        printf("pwhash_str failure\n");
    }
    if (crypto_pwhash_str(str_out2, passwd, strlen(passwd), OPSLIMIT,
                          MEMLIMIT) != 0) {
        printf("pwhash_str(2) failure\n");
    }
    if (strcmp(str_out, str_out2) == 0) {
        printf("pwhash_str() doesn't generate different salts\n");
    }
    if (crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT) != 0 ||
        crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT) != 0) {
        printf("needs_rehash() false positive\n");
    }
    if (crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT / 2) != 1 ||
        crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT - 1, MEMLIMIT) != 1 ||
        crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT * 2) != 1 ||
        crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT + 1, MEMLIMIT) != 1) {
        printf("needs_rehash() false negative (0)\n");
    }
    if (crypto_pwhash_argon2id_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT / 2) != 1 ||
        crypto_pwhash_argon2id_str_needs_rehash(str_out, OPSLIMIT - 1, MEMLIMIT) != 1 ||
        crypto_pwhash_argon2id_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT * 2) != 1 ||
        crypto_pwhash_argon2id_str_needs_rehash(str_out, OPSLIMIT + 1, MEMLIMIT) != 1) {
        printf("needs_rehash() false negative (1)\n");
    }
    if (crypto_pwhash_argon2i_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT / 2) != -1 ||
        crypto_pwhash_argon2i_str_needs_rehash(str_out, OPSLIMIT - 1, MEMLIMIT) != -1 ||
        crypto_pwhash_argon2i_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT * 2) != -1 ||
        crypto_pwhash_argon2i_str_needs_rehash(str_out, OPSLIMIT + 1, MEMLIMIT) != -1) {
        printf("needs_rehash() false negative (2)\n");
    }
    if (crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT / 2) != 1) {
        printf("pwhash_str_needs_rehash() didn't handle argon2id\n");
    }
    if (crypto_pwhash_str_needs_rehash(str_out + 1, OPSLIMIT, MEMLIMIT) != -1 ||
        crypto_pwhash_argon2id_str_needs_rehash(str_out + 1, OPSLIMIT, MEMLIMIT) != -1) {
        printf("needs_rehash() didn't fail with an invalid hash string\n");
    }
    if (sodium_is_zero((const unsigned char *) str_out + strlen(str_out),
                       crypto_pwhash_STRBYTES - strlen(str_out)) != 1 ||
        sodium_is_zero((const unsigned char *) str_out2 + strlen(str_out2),
                       crypto_pwhash_STRBYTES - strlen(str_out2)) != 1) {
        printf("pwhash_argon2id_str() doesn't properly pad with zeros\n");
    }
    if (crypto_pwhash_argon2id_str_verify(str_out, passwd, strlen(passwd)) != 0) {
        printf("pwhash_argon2id_str_verify(1) failure\n");
    }
    if (crypto_pwhash_str_verify(str_out, passwd, strlen(passwd)) != 0) {
        printf("pwhash_str_verify(1') failure\n");
    }
    str_out[14]++;
    if (crypto_pwhash_str_verify(str_out, passwd, strlen(passwd)) != -1) {
        printf("pwhash_argon2id_str_verify(2) failure\n");
    }
    str_out[14]--;
    assert(str_out[crypto_pwhash_argon2id_STRBYTES - 1U] == 0);

    if (crypto_pwhash_str(str_out2, passwd, 0x100000000ULL, OPSLIMIT,
                          MEMLIMIT) != -1) {
        printf("pwhash_str() with a large password should have failed\n");
    }
    if (crypto_pwhash_str(str_out2, passwd, strlen(passwd), 1, MEMLIMIT) != 0) {
        printf("pwhash_str() with a small opslimit should not have failed\n");
    }
    if (crypto_pwhash_str(str_out2, passwd, strlen(passwd), 0, MEMLIMIT) != -1) {
        printf("pwhash_argon2id_str() with a null opslimit should have failed\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$m=65536,t=2,p=1c29tZXNhbHQ"
                                 "$9sTbSlTio3Biev89thdrlKKiCaYsjjYVJxGAL3swxpQ",
                                 "password", 0x100000000ULL) != -1) {
        printf("pwhash_str_verify(invalid(0)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$m=65536,t=2,p=1c29tZXNhbHQ"
                                 "$9sTbSlTio3Biev89thdrlKKiCaYsjjYVJxGAL3swxpQ",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(1)) failure %d\n", errno);
    }
    if (crypto_pwhash_str_verify("$argon2id$m=65536,t=2,p=1$c29tZXNhbHQ"
                                 "9sTbSlTio3Biev89thdrlKKiCaYsjjYVJxGAL3swxpQ",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(2)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$m=65536,t=2,p=1$c29tZXNhbHQ"
                                 "$b2G3seW+uPzerwQQC+/E1K50CLLO7YXy0JRcaTuswRo",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(3)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=65536,t=2,p=1c29tZXNhbHQ"
                                 "$wWKIMhR9lyDFvRz9YTZweHKfbftvj+qf+YFY4NeBbtA",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(4)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=65536,t=2,p=1$c29tZXNhbHQ"
                                 "wWKIMhR9lyDFvRz9YTZweHKfbftvj+qf+YFY4NeBbtA",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(5)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=65536,t=2,p=1$c29tZXNhbHQ"
                                 "$8iIuixkI73Js3G1uMbezQXD0b8LG4SXGsOwoQkdAQIM",
                                 "password", strlen("password")) != -1) {
        printf("pwhash_str_verify(invalid(6)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=256,t=3,p=1$MDEyMzQ1Njc"
                                 "$G5ajKFCoUzaXRLdz7UJb5wGkb2Xt+X5/GQjUYtS2+TE",
                                 "password", strlen("password")) != 0) {
        printf("pwhash_str_verify(valid(7)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=256,t=3,p=1$MDEyMzQ1Njc"
                                 "$G5ajKFCoUzaXRLdz7UJb5wGkb2Xt+X5/GQjUYtS2+TE",
                                 "passwore", strlen("passwore")) != -1 || errno != EINVAL) {
        printf("pwhash_str_verify(invalid(7)) failure\n");
    }
    if (crypto_pwhash_str_verify("$Argon2id$v=19$m=256,t=3,p=1$MDEyMzQ1Njc"
                                 "$G5ajKFCoUzaXRLdz7UJb5wGkb2Xt+X5/GQjUYtS2+TE",
                                 "password", strlen("password")) != -1 || errno != EINVAL) {
        printf("pwhash_str_verify(invalid(8)) failure\n");
    }
    if (crypto_pwhash_str_verify("$argon2id$v=19$m=256,t=3,p=2$MDEyMzQ1Njc"
                                 "$G5ajKFCoUzaXRLdz7UJb5wGkb2Xt+X5/GQjUYtS2+TE",
                                 "password", strlen("password")) != -1 || errno != EINVAL) {
        printf("pwhash_str_verify(invalid(9)) failure\n");
    }
    assert(crypto_pwhash_str_alg(str_out, "test", 4, OPSLIMIT, MEMLIMIT,
                                 crypto_pwhash_ALG_ARGON2ID13) == 0);
    assert(crypto_pwhash_argon2id_str_verify(str_out, "test", 4) == 0);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out,
                                                   OPSLIMIT, MEMLIMIT) == 0);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out,
                                                   OPSLIMIT / 2, MEMLIMIT) == 1);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out,
                                                   OPSLIMIT, MEMLIMIT / 2) == 1);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out, 0, 0) == 1);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out, 0, 0) == -1);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out + 1,
                                                   OPSLIMIT, MEMLIMIT) == -1);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out, 0, 0) == -1);
    assert(crypto_pwhash_argon2i_str_needs_rehash("", OPSLIMIT, MEMLIMIT) == -1);
    assert(crypto_pwhash_str_alg(str_out, "test", 4, OPSLIMIT, MEMLIMIT,
                                 crypto_pwhash_ALG_ARGON2I13) == 0);
    assert(crypto_pwhash_argon2i_str_verify(str_out, "test", 4) == 0);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out,
                                                  OPSLIMIT, MEMLIMIT) == 0);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out,
                                                  OPSLIMIT / 2, MEMLIMIT) == 1);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out,
                                                  OPSLIMIT, MEMLIMIT / 2) == 1);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out, 0, 0) == 1);
    assert(crypto_pwhash_argon2id_str_needs_rehash(str_out, 0, 0) == -1);
    assert(crypto_pwhash_argon2i_str_needs_rehash("", OPSLIMIT, MEMLIMIT) == -1);
    assert(crypto_pwhash_argon2i_str_needs_rehash(str_out + 1,
                                                  OPSLIMIT, MEMLIMIT) == -1);
    sodium_free(salt);
    sodium_free(str_out);
    sodium_free(str_out2);
}