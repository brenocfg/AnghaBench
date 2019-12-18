#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {void** input; } ;
typedef  TYPE_1__ chacha_ctx ;

/* Variables and functions */
 void* U8TO32_LITTLE (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
chacha_ivsetup(chacha_ctx *x,const u8 *iv)
{
  x->input[12] = 0;
  x->input[13] = 0;
  x->input[14] = U8TO32_LITTLE(iv + 0);
  x->input[15] = U8TO32_LITTLE(iv + 4);
}