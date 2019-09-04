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
struct list_encoder {scalar_t__ k; scalar_t__ K; int /*<<< orphan*/  L; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpolative_encode_sublist (struct list_encoder*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void interpolative_encoder_finish (struct list_encoder *enc) {
  assert (enc->k == enc->K + 1);
  interpolative_encode_sublist (enc, 0, enc->K + 1);
  free (enc->L);
}