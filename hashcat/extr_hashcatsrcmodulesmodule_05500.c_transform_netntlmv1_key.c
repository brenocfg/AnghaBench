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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static void transform_netntlmv1_key (const u8 *nthash, u8 *key)
{
  key[0] =                    (nthash[0] >> 0);
  key[1] = (nthash[0] << 7) | (nthash[1] >> 1);
  key[2] = (nthash[1] << 6) | (nthash[2] >> 2);
  key[3] = (nthash[2] << 5) | (nthash[3] >> 3);
  key[4] = (nthash[3] << 4) | (nthash[4] >> 4);
  key[5] = (nthash[4] << 3) | (nthash[5] >> 5);
  key[6] = (nthash[5] << 2) | (nthash[6] >> 6);
  key[7] = (nthash[6] << 1);

  key[0] |= 0x01;
  key[1] |= 0x01;
  key[2] |= 0x01;
  key[3] |= 0x01;
  key[4] |= 0x01;
  key[5] |= 0x01;
  key[6] |= 0x01;
  key[7] |= 0x01;
}