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
 scalar_t__ crypto_aead_aegis256_ABYTES ; 
 scalar_t__ crypto_aead_aegis256_KEYBYTES ; 
 scalar_t__ crypto_aead_aegis256_MESSAGEBYTES_MAX ; 
 scalar_t__ crypto_aead_aegis256_NPUBBYTES ; 
 scalar_t__ crypto_aead_aegis256_NSECBYTES ; 
 scalar_t__ crypto_aead_aegis256_abytes () ; 
 scalar_t__ crypto_aead_aegis256_is_available () ; 
 scalar_t__ crypto_aead_aegis256_keybytes () ; 
 scalar_t__ crypto_aead_aegis256_messagebytes_max () ; 
 scalar_t__ crypto_aead_aegis256_npubbytes () ; 
 scalar_t__ crypto_aead_aegis256_nsecbytes () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tv () ; 

int
main(void)
{
    if (crypto_aead_aegis256_is_available()) {
        tv();
    }
    assert(crypto_aead_aegis256_keybytes() == crypto_aead_aegis256_KEYBYTES);
    assert(crypto_aead_aegis256_nsecbytes() == crypto_aead_aegis256_NSECBYTES);
    assert(crypto_aead_aegis256_npubbytes() == crypto_aead_aegis256_NPUBBYTES);
    assert(crypto_aead_aegis256_abytes() == crypto_aead_aegis256_ABYTES);
    assert(crypto_aead_aegis256_messagebytes_max() == crypto_aead_aegis256_MESSAGEBYTES_MAX);
    printf("OK\n");

    return 0;
}