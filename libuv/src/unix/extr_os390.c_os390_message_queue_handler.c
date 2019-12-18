#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  (* cb ) (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ uv_fs_event_t ;
struct TYPE_8__ {int msg_queue; } ;
typedef  TYPE_2__ uv__os390_epoll ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_9__ {scalar_t__ __rfim_event; scalar_t__ __rfim_utok; } ;
typedef  TYPE_3__ _RFIM ;

/* Variables and functions */
 scalar_t__ ENOMSG ; 
 int /*<<< orphan*/  IPC_NOWAIT ; 
 int UV_CHANGE ; 
 int UV_RENAME ; 
 scalar_t__ _RFIM_ATTR ; 
 scalar_t__ _RFIM_RENAME ; 
 scalar_t__ _RFIM_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 int msgrcv (int,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__basename_r (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int os390_message_queue_handler(uv__os390_epoll* ep) {
  uv_fs_event_t* handle;
  int msglen;
  int events;
  _RFIM msg;

  if (ep->msg_queue == -1)
    return 0;

  msglen = msgrcv(ep->msg_queue, &msg, sizeof(msg), 0, IPC_NOWAIT);

  if (msglen == -1 && errno == ENOMSG)
    return 0;

  if (msglen == -1)
    abort();

  events = 0;
  if (msg.__rfim_event == _RFIM_ATTR || msg.__rfim_event == _RFIM_WRITE)
    events = UV_CHANGE;
  else if (msg.__rfim_event == _RFIM_RENAME)
    events = UV_RENAME;
  else
    /* Some event that we are not interested in. */
    return 0;

  handle = *(uv_fs_event_t**)(msg.__rfim_utok);
  handle->cb(handle, uv__basename_r(handle->path), events, 0);
  return 1;
}