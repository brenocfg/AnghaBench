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
 int int_to_itoa64 (int) ; 

__attribute__((used)) static void sha1aix_encode (const u8 digest[20], u8 buf[27])
{
  int l;

  l = (digest[ 2] << 0) | (digest[ 1] << 8) | (digest[ 0] << 16);

  buf[ 0] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 1] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 2] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 3] = int_to_itoa64 (l & 0x3f);

  l = (digest[ 5] << 0) | (digest[ 4] << 8) | (digest[ 3] << 16);

  buf[ 4] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 5] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 6] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 7] = int_to_itoa64 (l & 0x3f);

  l = (digest[ 8] << 0) | (digest[ 7] << 8) | (digest[ 6] << 16);

  buf[ 8] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[ 9] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[10] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[11] = int_to_itoa64 (l & 0x3f);

  l = (digest[11] << 0) | (digest[10] << 8) | (digest[ 9] << 16);

  buf[12] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[13] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[14] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[15] = int_to_itoa64 (l & 0x3f);

  l = (digest[14] << 0) | (digest[13] << 8) | (digest[12] << 16);

  buf[16] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[17] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[18] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[19] = int_to_itoa64 (l & 0x3f);

  l = (digest[17] << 0) | (digest[16] << 8) | (digest[15] << 16);

  buf[20] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[21] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[22] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[23] = int_to_itoa64 (l & 0x3f);

  l =                 0 | (digest[19] << 8) | (digest[18] << 16);

  buf[24] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[25] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[26] = int_to_itoa64 (l & 0x3f);
}