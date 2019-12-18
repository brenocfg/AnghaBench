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
typedef  int /*<<< orphan*/  sl_symboltab ;

/* Variables and functions */
 int /*<<< orphan*/  ER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_block_decrypt ; 
 int /*<<< orphan*/  aes_block_encrypt ; 
 int /*<<< orphan*/  hmac_sha224 ; 
 int /*<<< orphan*/  hmac_sha256 ; 
 int /*<<< orphan*/  hmac_sha384 ; 
 int /*<<< orphan*/  hmac_sha512 ; 
 int /*<<< orphan*/  pbkdf2_sha224 ; 
 int /*<<< orphan*/  pbkdf2_sha256 ; 
 int /*<<< orphan*/  sha224 ; 
 int /*<<< orphan*/  sha256 ; 
 int /*<<< orphan*/  sha384 ; 
 int /*<<< orphan*/  sha512 ; 
 int /*<<< orphan*/  sl_symboltab_add_name_native (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int SL_MODULE_ENTRY(sl_symboltab *tab)
{
  ER(sl_symboltab_add_name_native(tab, "aes-encrypt", aes_block_encrypt));
  ER(sl_symboltab_add_name_native(tab, "aes-decrypt", aes_block_decrypt));
  ER(sl_symboltab_add_name_native(tab, "sha224", sha224));
  ER(sl_symboltab_add_name_native(tab, "sha256", sha256));
  ER(sl_symboltab_add_name_native(tab, "sha384", sha384));
  ER(sl_symboltab_add_name_native(tab, "sha512", sha512));
  ER(sl_symboltab_add_name_native(tab, "hmac-sha224", hmac_sha224));
  ER(sl_symboltab_add_name_native(tab, "hmac-sha256", hmac_sha256));
  ER(sl_symboltab_add_name_native(tab, "hmac-sha384", hmac_sha384));
  ER(sl_symboltab_add_name_native(tab, "hmac-sha512", hmac_sha512));
  ER(sl_symboltab_add_name_native(tab, "pbkdf2-sha224", pbkdf2_sha224));
  ER(sl_symboltab_add_name_native(tab, "pbkdf2-sha256", pbkdf2_sha256));
  return 0;
}