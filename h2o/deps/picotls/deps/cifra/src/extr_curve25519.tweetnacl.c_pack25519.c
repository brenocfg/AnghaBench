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
typedef  int uint8_t ;
typedef  int* gf ;

/* Variables and functions */
 int /*<<< orphan*/  car25519 (int*) ; 
 int /*<<< orphan*/  sel25519 (int*,int*,int) ; 
 int /*<<< orphan*/  set25519 (int*,int* const) ; 

__attribute__((used)) static void pack25519(uint8_t out[32], const gf n)
{
  size_t i, j;
  int b;
  gf m, t;
  set25519(t, n);
  car25519(t);
  car25519(t);
  car25519(t);
  
  for(j = 0; j < 2; j++)
  {
    m[0] = t[0] - 0xffed;
    for (i = 1; i < 15; i++)
    {
      m[i] = t[i] - 0xffff - ((m[i - 1] >> 16) & 1);
      m[i - 1] &= 0xffff;
    }
    m[15] = t[15] - 0x7fff - ((m[14] >> 16) & 1);
    b = (m[15] >> 16) & 1;
    m[14] &= 0xffff;
    sel25519(t, m, 1 - b);
  }

  for (i = 0; i < 16; i++)
  {
    out[2 * i] = t[i] & 0xff;
    out[2 * i + 1] = (uint8_t) (t[i] >> 8);
  }
}