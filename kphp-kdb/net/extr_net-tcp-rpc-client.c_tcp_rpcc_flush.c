#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  out; TYPE_1__* type; scalar_t__ crypto; } ;
struct TYPE_2__ {int (* crypto_needed_output_bytes ) (struct connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int rwm_push_data (int /*<<< orphan*/ *,int*,int) ; 
 int stub1 (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int tcp_rpcc_flush (struct connection *c) {
  if (c->crypto) {
    int pad_bytes = c->type->crypto_needed_output_bytes (c);
    vkprintf (2, "rpcs_flush: padding with %d bytes\n", pad_bytes);
    if (pad_bytes > 0) {
      assert (!(pad_bytes & 3));
      static int pad_str[3] = {4, 4, 4};
      assert (pad_bytes <= 12);
      assert (rwm_push_data (&c->out, pad_str, pad_bytes) == pad_bytes);
    }
    return pad_bytes;
  }
  return 0;
}