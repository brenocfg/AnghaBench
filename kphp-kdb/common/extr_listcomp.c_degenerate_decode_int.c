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
struct list_decoder {scalar_t__ k; scalar_t__ K; } ;

/* Variables and functions */

__attribute__((used)) static int degenerate_decode_int (struct list_decoder *dec) {
  if (dec->k >= dec->K) {  /* by K.O.T. */
    return 0x7fffffff;
  }
  return dec->k++;
}