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
struct transaction_buffer {int /*<<< orphan*/ * buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tb_free (struct transaction_buffer *B) {
  if (B->buff) {
    free (B->buff);
    B->buff = NULL;
  }
}