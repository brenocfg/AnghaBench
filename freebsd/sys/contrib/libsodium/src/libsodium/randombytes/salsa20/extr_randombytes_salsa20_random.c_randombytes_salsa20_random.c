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
struct TYPE_2__ {size_t rnd32_outleft; int /*<<< orphan*/ * rnd32; int /*<<< orphan*/  nonce; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int crypto_stream_salsa20 (unsigned char*,unsigned long long,unsigned char*,int /*<<< orphan*/ ) ; 
 int crypto_stream_salsa20_NONCEBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  randombytes_salsa20_random_stir_if_needed () ; 
 int /*<<< orphan*/  randombytes_salsa20_random_xorhwrand () ; 
 int /*<<< orphan*/  randombytes_salsa20_random_xorkey (int /*<<< orphan*/ *) ; 
 TYPE_1__ stream ; 

__attribute__((used)) static uint32_t
randombytes_salsa20_random(void)
{
    uint32_t val;
    int      ret;

    COMPILER_ASSERT(sizeof stream.rnd32 >= (sizeof stream.key) + (sizeof val));
    COMPILER_ASSERT(((sizeof stream.rnd32) - (sizeof stream.key))
                    % sizeof val == (size_t) 0U);
    if (stream.rnd32_outleft <= (size_t) 0U) {
        randombytes_salsa20_random_stir_if_needed();
        COMPILER_ASSERT(sizeof stream.nonce == crypto_stream_salsa20_NONCEBYTES);
        ret = crypto_stream_salsa20((unsigned char *) stream.rnd32,
                                    (unsigned long long) sizeof stream.rnd32,
                                    (unsigned char *) &stream.nonce,
                                    stream.key);
        assert(ret == 0);
        stream.rnd32_outleft = (sizeof stream.rnd32) - (sizeof stream.key);
        randombytes_salsa20_random_xorhwrand();
        randombytes_salsa20_random_xorkey(&stream.rnd32[stream.rnd32_outleft]);
        memset(&stream.rnd32[stream.rnd32_outleft], 0, sizeof stream.key);
        stream.nonce++;
    }
    stream.rnd32_outleft -= sizeof val;
    memcpy(&val, &stream.rnd32[stream.rnd32_outleft], sizeof val);
    memset(&stream.rnd32[stream.rnd32_outleft], 0, sizeof val);

    return val;
}