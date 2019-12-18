#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_upgrade ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

ws_status iwdp_on_upgrade(ws_t ws,
    const char *resource, const char *protocol,
    int version, const char *sec_key) {
  return ws->send_upgrade(ws);
}