#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rdk; } ;
typedef  TYPE_1__ AES_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  aes128_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes128_set_decrypt_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ td0 ; 
 scalar_t__ td1 ; 
 scalar_t__ td2 ; 
 scalar_t__ td3 ; 
 scalar_t__ td4 ; 
 scalar_t__ te0 ; 
 scalar_t__ te1 ; 
 scalar_t__ te2 ; 
 scalar_t__ te3 ; 

__attribute__((used)) static void AES128_decrypt_cbc (const u32 key[4], const u32 iv[4], const u32 in[16], u32 out[16])
{
  AES_KEY skey;

  aes128_set_decrypt_key (skey.rdk, key, (u32 *) te0, (u32 *) te1, (u32 *) te2, (u32 *) te3, (u32 *) td0, (u32 *) td1, (u32 *) td2, (u32 *) td3);

  u32 _iv[4] = { 0 };

  _iv[0] = iv[0];
  _iv[1] = iv[1];
  _iv[2] = iv[2];
  _iv[3] = iv[3];

  for (int i = 0; i < 16; i += 4)
  {
    u32 _in[4] = { 0 };
    u32 _out[4] = { 0 };

    _in[0] = in[i + 0];
    _in[1] = in[i + 1];
    _in[2] = in[i + 2];
    _in[3] = in[i + 3];

    aes128_decrypt (skey.rdk, _in, _out, (u32 *) td0, (u32 *) td1, (u32 *) td2, (u32 *) td3, (u32 *) td4);

    _out[0] ^= _iv[0];
    _out[1] ^= _iv[1];
    _out[2] ^= _iv[2];
    _out[3] ^= _iv[3];

    out[i + 0] = _out[0];
    out[i + 1] = _out[1];
    out[i + 2] = _out[2];
    out[i + 3] = _out[3];

    _iv[0] = _in[0];
    _iv[1] = _in[1];
    _iv[2] = _in[2];
    _iv[3] = _in[3];
  }
}