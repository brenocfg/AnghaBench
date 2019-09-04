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
struct TYPE_4__ {int /*<<< orphan*/  odd; int /*<<< orphan*/  evn; } ;
typedef  TYPE_1__ cf_sha3_bi ;

/* Variables and functions */
 int /*<<< orphan*/  rotl32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void rotl_bi_1(cf_sha3_bi *out, const cf_sha3_bi *in)
{
  /* in bit-interleaved representation, a rotation of 1
   * is a swap plus a single rotation of the odd word. */
  out->odd = rotl32(in->evn, 1);
  out->evn = in->odd;
}