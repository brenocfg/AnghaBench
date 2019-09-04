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
typedef  int Byte ;

/* Variables and functions */
 int kNumLogBits ; 

__attribute__((used)) static void LzmaEnc_FastPosInit(Byte *g_FastPos)
{
  unsigned slot;
  g_FastPos[0] = 0;
  g_FastPos[1] = 1;
  g_FastPos += 2;
  
  for (slot = 2; slot < kNumLogBits * 2; slot++)
  {
    size_t k = ((size_t)1 << ((slot >> 1) - 1));
    size_t j;
    for (j = 0; j < k; j++)
      g_FastPos[j] = (Byte)slot;
    g_FastPos += k;
  }
}