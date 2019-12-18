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
struct TYPE_2__ {int (* stream ) (unsigned char*,unsigned long long,unsigned char const*,unsigned char const*) ;} ;

/* Variables and functions */
 unsigned long long crypto_stream_chacha20_MESSAGEBYTES_MAX ; 
 TYPE_1__* implementation ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 int stub1 (unsigned char*,unsigned long long,unsigned char const*,unsigned char const*) ; 

int
crypto_stream_chacha20(unsigned char *c, unsigned long long clen,
                       const unsigned char *n, const unsigned char *k)
{
    if (clen > crypto_stream_chacha20_MESSAGEBYTES_MAX) {
        sodium_misuse();
    }
    return implementation->stream(c, clen, n, k);
}