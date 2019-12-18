#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nh_key; } ;
typedef  TYPE_1__ nh_ctx ;
typedef  int /*<<< orphan*/  aes_int_key ;

/* Variables and functions */
 int /*<<< orphan*/  endian_convert_if_le (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kdf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nh_reset (TYPE_1__*) ; 

__attribute__((used)) static void nh_init(nh_ctx *hc, aes_int_key prf_key)
/* Generate nh_key, endian convert and reset to be ready for hashing.   */
{
    kdf(hc->nh_key, prf_key, 1, sizeof(hc->nh_key));
    endian_convert_if_le(hc->nh_key, 4, sizeof(hc->nh_key));
    nh_reset(hc);
}