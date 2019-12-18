#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u64 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
struct TYPE_5__ {scalar_t__ hooks_buf; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_6__ {int hook_success; size_t* pubkey; size_t* ukey; } ;
typedef  TYPE_2__ electrum_hook_t ;
struct TYPE_7__ {int /*<<< orphan*/  ephemeral_pubkey_struct; } ;
typedef  TYPE_3__ electrum_hook_salt_t ;

/* Variables and functions */
 int hc_secp256k1_pubkey_tweak_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 

void module_hook23 (hc_device_param_t *device_param, const void *hook_salts_buf, const u32 salt_pos, const u64 pw_pos)
{
  electrum_hook_t *hook_items = (electrum_hook_t *) device_param->hooks_buf;

  electrum_hook_salt_t *electrums = (electrum_hook_salt_t *) hook_salts_buf;
  electrum_hook_salt_t *electrum  = &electrums[salt_pos];

  // we need to copy it because the secp256k1_ec_pubkey_tweak_mul () function has side effects

  secp256k1_pubkey ephemeral_pubkey = electrum->ephemeral_pubkey_struct; // shallow copy is safe !

  // this hook data needs to be updated (the "hook_success" variable):

  electrum_hook_t *hook_item = &hook_items[pw_pos];

  hook_item->hook_success = 0;

  u32 *hook_pubkey = hook_item->pubkey;

  hook_pubkey[0] = hook_item->ukey[0];
  hook_pubkey[1] = hook_item->ukey[1];
  hook_pubkey[2] = hook_item->ukey[2];
  hook_pubkey[3] = hook_item->ukey[3];
  hook_pubkey[4] = hook_item->ukey[4];
  hook_pubkey[5] = hook_item->ukey[5];
  hook_pubkey[6] = hook_item->ukey[6];
  hook_pubkey[7] = hook_item->ukey[7];
  hook_pubkey[8] = 0;

  /*
   * Start with Elliptic Curve Cryptography (ECC)
   */

  const size_t length = 33; // NOT a bug (32 + 1 for the sign)

  bool multiply_success = hc_secp256k1_pubkey_tweak_mul (&ephemeral_pubkey, (u8 *) hook_pubkey, length);

  if (multiply_success == false) return;

  // in this case hook_success set to 1 doesn't mean that we've cracked it, but just that there were
  // no problems detected by secp256k1_ec_pubkey_tweak_mul ()

  hook_item->hook_success = 1;
}