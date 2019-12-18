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
struct TYPE_4__ {int unprocessed_bytes; } ;
struct TYPE_3__ {int total_bytes; } ;
struct connection {int flags; TYPE_2__ Out; TYPE_1__ out; scalar_t__ crypto; } ;

/* Variables and functions */
 int C_RAWMSG ; 

int out_total_unprocessed_bytes (struct connection *c) {
  if (c->flags & C_RAWMSG) {
    return (c->crypto ? c->out.total_bytes : 0);
  } else {
    return c->Out.unprocessed_bytes;
  }
}