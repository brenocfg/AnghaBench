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
struct TYPE_2__ {int unprocessed_bytes; } ;
struct connection {TYPE_1__ Out; int /*<<< orphan*/  crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int aes_crypto_needed_output_bytes (struct connection *c) {
  assert (c->crypto);
  return -c->Out.unprocessed_bytes & 15;
}