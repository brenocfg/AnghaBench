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
typedef  int /*<<< orphan*/  XXH32_state_t ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_checkResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH32 (void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH32_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH32_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH32_update (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void BMK_testSequence(const void* sequence, size_t len, U32 seed, U32 Nresult)
{
    XXH32_state_t state;
    U32 Dresult;
    size_t pos;

    Dresult = XXH32(sequence, len, seed);
    BMK_checkResult(Dresult, Nresult);

    XXH32_reset(&state, seed);
    XXH32_update(&state, sequence, len);
    Dresult = XXH32_digest(&state);
    BMK_checkResult(Dresult, Nresult);

    XXH32_reset(&state, seed);
    for (pos=0; pos<len; pos++)
        XXH32_update(&state, ((const char*)sequence)+pos, 1);
    Dresult = XXH32_digest(&state);
    BMK_checkResult(Dresult, Nresult);
}