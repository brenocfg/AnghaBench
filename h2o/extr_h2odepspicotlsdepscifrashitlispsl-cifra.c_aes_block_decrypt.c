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
typedef  int /*<<< orphan*/  sl_value ;
typedef  int /*<<< orphan*/  sl_symboltab ;

/* Variables and functions */
 int /*<<< orphan*/ * aes_block_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_aes_decrypt ; 

__attribute__((used)) static sl_value * aes_block_decrypt(sl_value *self, sl_value *args, sl_symboltab *tab)
{
  return aes_block_fn(self, args, tab, cf_aes_decrypt);
}