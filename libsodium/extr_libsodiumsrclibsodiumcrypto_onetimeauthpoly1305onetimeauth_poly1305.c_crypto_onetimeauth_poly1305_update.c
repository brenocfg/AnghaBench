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
typedef  int /*<<< orphan*/  crypto_onetimeauth_poly1305_state ;
struct TYPE_2__ {int (* onetimeauth_update ) (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ;} ;

/* Variables and functions */
 TYPE_1__* implementation ; 
 int stub1 (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 

int
crypto_onetimeauth_poly1305_update(crypto_onetimeauth_poly1305_state *state,
                                   const unsigned char *in,
                                   unsigned long long inlen)
{
    return implementation->onetimeauth_update(state, in, inlen);
}