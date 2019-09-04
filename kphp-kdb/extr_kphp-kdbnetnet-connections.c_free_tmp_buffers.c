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
struct connection {scalar_t__ Tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_buffers (scalar_t__) ; 

int free_tmp_buffers (struct connection *c) {
  if (c->Tmp) {
    free_all_buffers (c->Tmp);
    c->Tmp = 0;
  }
  return 0;
}