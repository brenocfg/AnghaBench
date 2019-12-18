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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AES128_decrypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base64_decode (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base64_to_int ; 
 int /*<<< orphan*/  byte_swap_32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void juniper_decrypt_hash (const u8 *in, const int in_len, u8 *out)
{
  // base64 decode

  u8 base64_buf[100] = { 0 };

  base64_decode (base64_to_int, (const u8 *) in, in_len, base64_buf);

  // iv stuff

  u32 juniper_iv[4] = { 0 };

  memcpy (juniper_iv, base64_buf, 12);

  memcpy (out, juniper_iv, 12);

  // reversed key

  u32 juniper_key[4] = { 0 };

  juniper_key[0] = byte_swap_32 (0xa6707a7e);
  juniper_key[1] = byte_swap_32 (0x8df91059);
  juniper_key[2] = byte_swap_32 (0xdea70ae5);
  juniper_key[3] = byte_swap_32 (0x2f9c2442);

  // AES decrypt

  u32 *in_ptr  = (u32 *) (base64_buf + 12);
  u32 *out_ptr = (u32 *) (out        + 12);

  AES128_decrypt_cbc (juniper_key, juniper_iv, in_ptr, out_ptr);
}