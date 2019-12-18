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
typedef  scalar_t__ UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  FT4 (int) ; 
 int /*<<< orphan*/  HT16 (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void Aes_Encode(const UInt32 *w, UInt32 *dest, const UInt32 *src)
{
  UInt32 s[4];
  UInt32 m[4];
  UInt32 numRounds2 = w[0];
  w += 4;
  s[0] = src[0] ^ w[0];
  s[1] = src[1] ^ w[1];
  s[2] = src[2] ^ w[2];
  s[3] = src[3] ^ w[3];
  w += 4;
  for (;;)
  {
    HT16(m, s, 0);
    if (--numRounds2 == 0)
      break;
    HT16(s, m, 4);
    w += 8;
  }
  w += 4;
  FT4(0); FT4(1); FT4(2); FT4(3);
}