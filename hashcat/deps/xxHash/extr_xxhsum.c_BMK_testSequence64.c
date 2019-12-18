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
typedef  int /*<<< orphan*/  XXH64_state_t ;
typedef  int /*<<< orphan*/  U64 ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_checkResult64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64 (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void BMK_testSequence64(void* sentence, size_t len, U64 seed, U64 Nresult)
{
    XXH64_state_t state;
    U64 Dresult;
    size_t pos;

    Dresult = XXH64(sentence, len, seed);
    BMK_checkResult64(Dresult, Nresult);

    XXH64_reset(&state, seed);
    XXH64_update(&state, sentence, len);
    Dresult = XXH64_digest(&state);
    BMK_checkResult64(Dresult, Nresult);

    XXH64_reset(&state, seed);
    for (pos=0; pos<len; pos++)
        XXH64_update(&state, ((char*)sentence)+pos, 1);
    Dresult = XXH64_digest(&state);
    BMK_checkResult64(Dresult, Nresult);
}