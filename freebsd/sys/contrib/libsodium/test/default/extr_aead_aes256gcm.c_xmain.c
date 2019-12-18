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
typedef  int /*<<< orphan*/  crypto_aead_aes256gcm_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_aead_aes256gcm_ABYTES ; 
 scalar_t__ crypto_aead_aes256gcm_KEYBYTES ; 
 scalar_t__ crypto_aead_aes256gcm_MESSAGEBYTES_MAX ; 
 scalar_t__ crypto_aead_aes256gcm_NPUBBYTES ; 
 scalar_t__ crypto_aead_aes256gcm_NSECBYTES ; 
 scalar_t__ crypto_aead_aes256gcm_abytes () ; 
 scalar_t__ crypto_aead_aes256gcm_is_available () ; 
 scalar_t__ crypto_aead_aes256gcm_keybytes () ; 
 scalar_t__ crypto_aead_aes256gcm_messagebytes_max () ; 
 scalar_t__ crypto_aead_aes256gcm_npubbytes () ; 
 scalar_t__ crypto_aead_aes256gcm_nsecbytes () ; 
 int crypto_aead_aes256gcm_statebytes () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tv () ; 

int
main(void)
{
    if (crypto_aead_aes256gcm_is_available()) {
        tv();
    }
    assert(crypto_aead_aes256gcm_keybytes() == crypto_aead_aes256gcm_KEYBYTES);
    assert(crypto_aead_aes256gcm_nsecbytes() == crypto_aead_aes256gcm_NSECBYTES);
    assert(crypto_aead_aes256gcm_npubbytes() == crypto_aead_aes256gcm_NPUBBYTES);
    assert(crypto_aead_aes256gcm_abytes() == crypto_aead_aes256gcm_ABYTES);
    assert(crypto_aead_aes256gcm_statebytes() >= sizeof(crypto_aead_aes256gcm_state));
    assert(crypto_aead_aes256gcm_messagebytes_max() == crypto_aead_aes256gcm_MESSAGEBYTES_MAX);
    printf("OK\n");

    return 0;
}