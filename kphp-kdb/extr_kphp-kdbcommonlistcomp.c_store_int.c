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
struct list_encoder {int* L; int /*<<< orphan*/  k; } ;

/* Variables and functions */

__attribute__((used)) static void store_int (struct list_encoder *enc, int d) {
  /* just store in internal array for further compression */
  enc->L[enc->k++] = d;
}