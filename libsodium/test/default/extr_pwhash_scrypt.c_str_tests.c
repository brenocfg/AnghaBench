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
 int MEMLIMIT ; 
 int OPSLIMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_SALTBYTES ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_STRBYTES ; 
 scalar_t__ crypto_pwhash_scryptsalsa208sha256_str (char*,char const*,int /*<<< orphan*/ ,int,int) ; 
 int crypto_pwhash_scryptsalsa208sha256_str_needs_rehash (char*,int,int) ; 
 scalar_t__ crypto_pwhash_scryptsalsa208sha256_str_verify (char*,char const*,int /*<<< orphan*/ ) ; 
 int crypto_pwhash_str_needs_rehash (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sodium_free (char*) ; 
 scalar_t__ sodium_malloc (unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
str_tests(void)
{
    char       *str_out;
    char       *str_out2;
    char       *salt;
    const char *passwd = "Correct Horse Battery Staple";

    salt = (char *) sodium_malloc(crypto_pwhash_scryptsalsa208sha256_SALTBYTES);
    str_out =
        (char *) sodium_malloc(crypto_pwhash_scryptsalsa208sha256_STRBYTES);
    str_out2 =
        (char *) sodium_malloc(crypto_pwhash_scryptsalsa208sha256_STRBYTES);
    memcpy(salt, "[<~A 32-bytes salt for scrypt~>]",
           crypto_pwhash_scryptsalsa208sha256_SALTBYTES);
    if (crypto_pwhash_scryptsalsa208sha256_str(str_out, passwd, strlen(passwd),
                                               OPSLIMIT, MEMLIMIT) != 0) {
        printf("pwhash_str failure\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str(str_out2, passwd, strlen(passwd),
                                               OPSLIMIT, MEMLIMIT) != 0) {
        printf("pwhash_str(2) failure\n");
    }
    if (strcmp(str_out, str_out2) == 0) {
        printf("pwhash_str doesn't generate different salts\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out, OPSLIMIT, MEMLIMIT) != 0) {
        printf("needs_rehash() false positive\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out, OPSLIMIT, MEMLIMIT / 2) != 1 ||
        crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out, OPSLIMIT / 2, MEMLIMIT) != 1 ||
        crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out, OPSLIMIT, MEMLIMIT * 2) != 1 ||
        crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out, OPSLIMIT * 2, MEMLIMIT) != 1) {
        printf("needs_rehash() false negative\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
        (str_out + 1, OPSLIMIT, MEMLIMIT) != -1) {
        printf("needs_rehash() didn't fail with an invalid hash string\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str_verify(str_out, passwd,
                                                      strlen(passwd)) != 0) {
        printf("pwhash_str_verify failure\n");
    }
    if (crypto_pwhash_scryptsalsa208sha256_str_verify(str_out, passwd,
                                                      strlen(passwd)) != 0) {
        printf("pwhash_str_verify failure\n");
    }
    str_out[14]++;
    if (crypto_pwhash_scryptsalsa208sha256_str_verify(str_out, passwd,
                                                      strlen(passwd)) == 0) {
        printf("pwhash_str_verify(2) failure\n");
    }
    str_out[14]--;

    assert(str_out[crypto_pwhash_scryptsalsa208sha256_STRBYTES - 1U] == 0);

    assert(crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
           (str_out, 0, 0) == 1);
    assert(crypto_pwhash_str_needs_rehash(str_out, 0, 0) == -1);
    assert(crypto_pwhash_str_needs_rehash(str_out, OPSLIMIT, MEMLIMIT) == -1);
    assert(crypto_pwhash_scryptsalsa208sha256_str_needs_rehash
           ("", OPSLIMIT, MEMLIMIT) == -1);

    sodium_free(salt);
    sodium_free(str_out);
    sodium_free(str_out2);
}