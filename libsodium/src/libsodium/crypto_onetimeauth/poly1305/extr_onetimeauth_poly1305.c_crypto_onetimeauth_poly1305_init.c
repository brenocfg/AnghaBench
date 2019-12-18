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
struct TYPE_2__ {int (* onetimeauth_init ) (int /*<<< orphan*/ *,unsigned char const*) ;} ;

/* Variables and functions */
 TYPE_1__* implementation ; 
 int stub1 (int /*<<< orphan*/ *,unsigned char const*) ; 

int
crypto_onetimeauth_poly1305_init(crypto_onetimeauth_poly1305_state *state,
                                 const unsigned char *key)
{
    return implementation->onetimeauth_init(state, key);
}