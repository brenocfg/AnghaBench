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
typedef  int /*<<< orphan*/  ws_status ;
typedef  size_t ssize_t ;
typedef  TYPE_2__* my_t ;
struct TYPE_5__ {int fd; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_ERROR ; 
 int /*<<< orphan*/  WS_SUCCESS ; 
 size_t send (int,void*,size_t,int /*<<< orphan*/ ) ; 

ws_status send_data(ws_t ws, const char *data, size_t length) {
  int fd = ((my_t)ws->state)->fd;
  ssize_t sent_bytes = send(fd, (void*)data, length, 0);
  return (sent_bytes == length ? WS_SUCCESS : WS_ERROR);
}