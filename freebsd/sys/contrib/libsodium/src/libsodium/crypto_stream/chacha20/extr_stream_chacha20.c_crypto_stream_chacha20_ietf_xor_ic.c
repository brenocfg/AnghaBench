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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int (* stream_ietf_xor_ic ) (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*) ;} ;

/* Variables and functions */
 TYPE_1__* implementation ; 
 int stub1 (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*) ; 

int
crypto_stream_chacha20_ietf_xor_ic(unsigned char *c, const unsigned char *m,
                                   unsigned long long mlen,
                                   const unsigned char *n, uint32_t ic,
                                   const unsigned char *k)
{
    return implementation->stream_ietf_xor_ic(c, m, mlen, n, ic, k);
}