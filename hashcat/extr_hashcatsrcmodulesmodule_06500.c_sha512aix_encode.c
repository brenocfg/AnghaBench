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

__attribute__((used)) static void sha512aix_encode (const u8 digest[64], u8 buf[86])
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

  l = (digest[20] << 0) | (digest[19] << 8) | (digest[18] << 16);

  buf[24] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[25] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[26] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[27] = int_to_itoa64 (l & 0x3f);

  l = (digest[23] << 0) | (digest[22] << 8) | (digest[21] << 16);

  buf[28] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[29] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[30] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[31] = int_to_itoa64 (l & 0x3f);

  l = (digest[26] << 0) | (digest[25] << 8) | (digest[24] << 16);

  buf[32] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[33] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[34] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[35] = int_to_itoa64 (l & 0x3f);

  l = (digest[29] << 0) | (digest[28] << 8) | (digest[27] << 16);

  buf[36] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[37] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[38] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[39] = int_to_itoa64 (l & 0x3f);

  l = (digest[32] << 0) | (digest[31] << 8) | (digest[30] << 16);

  buf[40] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[41] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[42] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[43] = int_to_itoa64 (l & 0x3f);

  l = (digest[35] << 0) | (digest[34] << 8) | (digest[33] << 16);

  buf[44] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[45] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[46] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[47] = int_to_itoa64 (l & 0x3f);

  l = (digest[38] << 0) | (digest[37] << 8) | (digest[36] << 16);

  buf[48] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[49] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[50] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[51] = int_to_itoa64 (l & 0x3f);

  l = (digest[41] << 0) | (digest[40] << 8) | (digest[39] << 16);

  buf[52] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[53] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[54] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[55] = int_to_itoa64 (l & 0x3f);

  l = (digest[44] << 0) | (digest[43] << 8) | (digest[42] << 16);

  buf[56] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[57] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[58] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[59] = int_to_itoa64 (l & 0x3f);

  l = (digest[47] << 0) | (digest[46] << 8) | (digest[45] << 16);

  buf[60] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[61] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[62] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[63] = int_to_itoa64 (l & 0x3f);

  l = (digest[50] << 0) | (digest[49] << 8) | (digest[48] << 16);

  buf[64] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[65] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[66] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[67] = int_to_itoa64 (l & 0x3f);

  l = (digest[53] << 0) | (digest[52] << 8) | (digest[51] << 16);

  buf[68] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[69] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[70] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[71] = int_to_itoa64 (l & 0x3f);

  l = (digest[56] << 0) | (digest[55] << 8) | (digest[54] << 16);

  buf[72] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[73] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[74] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[75] = int_to_itoa64 (l & 0x3f);

  l = (digest[59] << 0) | (digest[58] << 8) | (digest[57] << 16);

  buf[76] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[77] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[78] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[79] = int_to_itoa64 (l & 0x3f);

  l = (digest[62] << 0) | (digest[61] << 8) | (digest[60] << 16);

  buf[80] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[81] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[82] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[83] = int_to_itoa64 (l & 0x3f);

  l =                                         (digest[63] << 16);

  buf[84] = int_to_itoa64 (l & 0x3f); l >>= 6;
  buf[85] = int_to_itoa64 (l & 0x3f); //l >>= 6;
}