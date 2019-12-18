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
 unsigned int crypto_stream_chacha20_KEYBYTES ; 
 scalar_t__ crypto_stream_chacha20_MESSAGEBYTES_MAX ; 
 unsigned int crypto_stream_chacha20_NONCEBYTES ; 
 unsigned int crypto_stream_chacha20_ietf_KEYBYTES ; 
 scalar_t__ crypto_stream_chacha20_ietf_MESSAGEBYTES_MAX ; 
 unsigned int crypto_stream_chacha20_ietf_NONCEBYTES ; 
 unsigned int crypto_stream_chacha20_ietf_keybytes () ; 
 scalar_t__ crypto_stream_chacha20_ietf_messagebytes_max () ; 
 unsigned int crypto_stream_chacha20_ietf_noncebytes () ; 
 unsigned int crypto_stream_chacha20_keybytes () ; 
 scalar_t__ crypto_stream_chacha20_messagebytes_max () ; 
 unsigned int crypto_stream_chacha20_noncebytes () ; 
 int /*<<< orphan*/  tv () ; 
 int /*<<< orphan*/  tv_ietf () ; 

int
main(void)
{
    tv();
    tv_ietf();

    assert(crypto_stream_chacha20_keybytes() > 0U);
    assert(crypto_stream_chacha20_keybytes() == crypto_stream_chacha20_KEYBYTES);
    assert(crypto_stream_chacha20_noncebytes() > 0U);
    assert(crypto_stream_chacha20_noncebytes() == crypto_stream_chacha20_NONCEBYTES);
    assert(crypto_stream_chacha20_messagebytes_max() == crypto_stream_chacha20_MESSAGEBYTES_MAX);
    assert(crypto_stream_chacha20_ietf_keybytes() > 0U);
    assert(crypto_stream_chacha20_ietf_keybytes() == crypto_stream_chacha20_ietf_KEYBYTES);
    assert(crypto_stream_chacha20_ietf_noncebytes() > 0U);
    assert(crypto_stream_chacha20_ietf_noncebytes() == crypto_stream_chacha20_ietf_NONCEBYTES);
    assert(crypto_stream_chacha20_ietf_messagebytes_max() == crypto_stream_chacha20_ietf_MESSAGEBYTES_MAX);

    return 0;
}