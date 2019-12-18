#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
struct my_struct {int dummy; } ;
typedef  TYPE_2__* my_t ;
struct TYPE_8__ {int fd; int port; TYPE_1__* ws; } ;
struct TYPE_7__ {TYPE_2__* state; int /*<<< orphan*/  on_frame; int /*<<< orphan*/  on_upgrade; int /*<<< orphan*/  on_http_request; int /*<<< orphan*/  send_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_frame ; 
 int /*<<< orphan*/  on_http_request ; 
 int /*<<< orphan*/  on_upgrade ; 
 int /*<<< orphan*/  send_data ; 
 TYPE_1__* ws_new () ; 

my_t my_new(int fd, int port) {
  my_t my = (my_t)malloc(sizeof(struct my_struct));
  ws_t ws = ws_new();
  if (!ws || !my) {
    free(ws);
    return NULL;
  }
  memset(my, 0, sizeof(struct my_struct));
  my->fd = fd;
  my->port = port;
  my->ws = ws;
  ws->send_data = send_data;
  ws->on_http_request = on_http_request;
  ws->on_upgrade = on_upgrade;
  ws->on_frame = on_frame;
  ws->state = my;
  return my;
}