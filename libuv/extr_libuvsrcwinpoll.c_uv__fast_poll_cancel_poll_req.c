#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ socket; } ;
typedef  TYPE_3__ uv_poll_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_7__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_10__ {int NumberOfHandles; TYPE_2__* Handles; TYPE_1__ Timeout; int /*<<< orphan*/  Exclusive; } ;
struct TYPE_8__ {int /*<<< orphan*/  Events; scalar_t__ Status; scalar_t__ Handle; } ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ AFD_POLL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_POLL_ALL ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ WSA_IO_PENDING ; 
 int /*<<< orphan*/  uv__get_afd_poll_info_dummy () ; 
 int /*<<< orphan*/  uv__get_overlapped_dummy () ; 
 int uv_msafd_poll (scalar_t__,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uv__fast_poll_cancel_poll_req(uv_loop_t* loop, uv_poll_t* handle) {
  AFD_POLL_INFO afd_poll_info;
  int result;

  afd_poll_info.Exclusive = TRUE;
  afd_poll_info.NumberOfHandles = 1;
  afd_poll_info.Timeout.QuadPart = INT64_MAX;
  afd_poll_info.Handles[0].Handle = (HANDLE) handle->socket;
  afd_poll_info.Handles[0].Status = 0;
  afd_poll_info.Handles[0].Events = AFD_POLL_ALL;

  result = uv_msafd_poll(handle->socket,
                         &afd_poll_info,
                         uv__get_afd_poll_info_dummy(),
                         uv__get_overlapped_dummy());

  if (result == SOCKET_ERROR) {
    DWORD error = WSAGetLastError();
    if (error != WSA_IO_PENDING)
      return error;
  }

  return 0;
}