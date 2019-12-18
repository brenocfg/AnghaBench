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
struct mrb_hmac {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,struct mrb_hmac*) ; 

__attribute__((used)) static void
lib_hmac_free(mrb_state *mrb, void *ptr)
{
  struct mrb_hmac *hmac = ptr;
  if (hmac != NULL)
    mrb_free(mrb, hmac);
}