#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_2__* my_t ;
struct TYPE_5__ {TYPE_1__* ws; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_recv ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

sm_status on_recv(sm_t sm, int fd, void *value,
    const char *buf, ssize_t length) {
  ws_t ws = ((my_t)value)->ws;
  return ws->on_recv(ws, buf, length);
}