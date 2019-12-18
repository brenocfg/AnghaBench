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
typedef  int /*<<< orphan*/  jv_nomem_handler_f ;
struct TYPE_2__ {void* data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 TYPE_1__ nomem_handler ; 

void jv_nomem_handler(jv_nomem_handler_f handler, void *data) {
  nomem_handler.handler = handler;
  nomem_handler.data = data;
}