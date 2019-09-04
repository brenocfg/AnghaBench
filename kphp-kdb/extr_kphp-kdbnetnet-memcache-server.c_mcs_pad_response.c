#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ status; int /*<<< orphan*/  Out; TYPE_1__* type; } ;
struct TYPE_4__ {int crypto_flags; } ;
struct TYPE_3__ {int (* crypto_needed_output_bytes ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* MCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_expect_query ; 
 int stub1 (struct connection*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

void mcs_pad_response (struct connection *c) {
  if (c->status == conn_expect_query && (MCS_DATA(c)->crypto_flags & 8)) {
    int pad_bytes = c->type->crypto_needed_output_bytes (c);
    if (pad_bytes > 0) {
      static char pad_str[16] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
      assert (pad_bytes <= 15);
      write_out (&c->Out, pad_str, pad_bytes);
    }
  }
}