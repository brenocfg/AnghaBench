#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; } ;
struct TYPE_9__ {TYPE_2__ io_watcher; } ;
typedef  TYPE_3__ uv_udp_t ;
struct TYPE_7__ {int fd; } ;
struct TYPE_10__ {TYPE_1__ io_watcher; } ;
typedef  TYPE_4__ uv_stream_t ;
struct TYPE_11__ {int type; } ;
typedef  TYPE_5__ uv_handle_t ;

/* Variables and functions */
#define  UV_NAMED_PIPE 130 
#define  UV_TCP 129 
#define  UV_UDP 128 

__attribute__((used)) static int uv__handle_fd(uv_handle_t* handle) {
  switch (handle->type) {
    case UV_NAMED_PIPE:
    case UV_TCP:
      return ((uv_stream_t*) handle)->io_watcher.fd;

    case UV_UDP:
      return ((uv_udp_t*) handle)->io_watcher.fd;

    default:
      return -1;
  }
}