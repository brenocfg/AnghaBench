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
struct list_decoder {int M; int /*<<< orphan*/  br; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int bread_nbits (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static int llrun_decode_int_single_bucket (struct list_decoder *dec) {
  const int o = dec->M;
  return dec->last += bread_nbits (&dec->br, o) + (1 << o);
}