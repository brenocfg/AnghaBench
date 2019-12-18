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
typedef  int UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  FD4 (int) ; 
 int /*<<< orphan*/  HD16 (int*,int*,int) ; 

__attribute__((used)) static void Aes_Decode(const UInt32 *w, UInt32 *dest, const UInt32 *src)
{
  UInt32 s[4];
  UInt32 m[4];
  UInt32 numRounds2 = w[0];
  w += 4 + numRounds2 * 8;
  s[0] = src[0] ^ w[0];
  s[1] = src[1] ^ w[1];
  s[2] = src[2] ^ w[2];
  s[3] = src[3] ^ w[3];
  for (;;)
  {
    w -= 8;
    HD16(m, s, 4);
    if (--numRounds2 == 0)
      break;
    HD16(s, m, 0);
  }
  FD4(0); FD4(1); FD4(2); FD4(3);
}