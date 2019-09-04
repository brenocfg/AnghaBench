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

/* Variables and functions */
 int /*<<< orphan*/  vector (char*,char*,char*) ; 

__attribute__((used)) static void test_vectors(void)
{
  vector("00112233445566778899aabbccddeeff", "69c4e0d86a7b0430d8cdb78070b4c55a",
         "000102030405060708090a0b0c0d0e0f");
  vector("00112233445566778899aabbccddeeff", "dda97ca4864cdfe06eaf70a0ec0d7191",
         "000102030405060708090a0b0c0d0e0f1011121314151617");
  vector("00112233445566778899aabbccddeeff", "8ea2b7ca516745bfeafc49904b496089",
         "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
}