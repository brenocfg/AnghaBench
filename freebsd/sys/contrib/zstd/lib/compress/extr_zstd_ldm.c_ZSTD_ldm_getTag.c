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
typedef  int U64 ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static U32 ZSTD_ldm_getTag(U64 hash, U32 hbits, U32 numTagBits)
{
    assert(numTagBits < 32 && hbits <= 32);
    if (32 - hbits < numTagBits) {
        return hash & (((U32)1 << numTagBits) - 1);
    } else {
        return (hash >> (32 - hbits - numTagBits)) & (((U32)1 << numTagBits) - 1);
    }
}