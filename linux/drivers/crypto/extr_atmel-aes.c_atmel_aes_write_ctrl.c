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
struct atmel_aes_dev {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_aes_write_ctrl_key (struct atmel_aes_dev*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atmel_aes_write_ctrl(struct atmel_aes_dev *dd, bool use_dma,
					const u32 *iv)

{
	atmel_aes_write_ctrl_key(dd, use_dma, iv,
				 dd->ctx->key, dd->ctx->keylen);
}