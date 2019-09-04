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
typedef  scalar_t__ XXH_endianess ;
typedef  int /*<<< orphan*/  XXH64_state_t ;

/* Variables and functions */
 unsigned long long XXH64_digest_endian (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  XXH_CPU_LITTLE_ENDIAN ; 
 scalar_t__ XXH_FORCE_NATIVE_FORMAT ; 
 scalar_t__ XXH_bigEndian ; 
 scalar_t__ XXH_littleEndian ; 

unsigned long long XXH64_digest (const XXH64_state_t* state_in)
{
    XXH_endianess endian_detected = (XXH_endianess)XXH_CPU_LITTLE_ENDIAN;

    if ((endian_detected==XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
        return XXH64_digest_endian(state_in, XXH_littleEndian);
    else
        return XXH64_digest_endian(state_in, XXH_bigEndian);
}