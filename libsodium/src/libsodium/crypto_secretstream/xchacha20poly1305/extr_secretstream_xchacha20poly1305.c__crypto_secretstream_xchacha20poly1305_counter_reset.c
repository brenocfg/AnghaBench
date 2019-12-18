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
typedef  int /*<<< orphan*/  crypto_secretstream_xchacha20poly1305_state ;

/* Variables and functions */
 int* STATE_COUNTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_secretstream_xchacha20poly1305_COUNTERBYTES ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
_crypto_secretstream_xchacha20poly1305_counter_reset
    (crypto_secretstream_xchacha20poly1305_state *state)
{
    memset(STATE_COUNTER(state), 0,
           crypto_secretstream_xchacha20poly1305_COUNTERBYTES);
    STATE_COUNTER(state)[0] = 1;
}