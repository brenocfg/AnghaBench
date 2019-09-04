#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* poll_peer_sockets; int /*<<< orphan*/  iocp; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_7__ {int /*<<< orphan*/  ProviderId; } ;
typedef  TYPE_2__ WSAPROTOCOL_INFOW ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ memcmp (void*,void*,int) ; 
 scalar_t__ uv__fast_poll_create_peer_socket (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * uv_msafd_provider_ids ; 

__attribute__((used)) static SOCKET uv__fast_poll_get_peer_socket(uv_loop_t* loop,
    WSAPROTOCOL_INFOW* protocol_info) {
  int index, i;
  SOCKET peer_socket;

  index = -1;
  for (i = 0; (size_t) i < ARRAY_SIZE(uv_msafd_provider_ids); i++) {
    if (memcmp((void*) &protocol_info->ProviderId,
               (void*) &uv_msafd_provider_ids[i],
               sizeof protocol_info->ProviderId) == 0) {
      index = i;
    }
  }

  /* Check if the protocol uses an msafd socket. */
  if (index < 0) {
    return INVALID_SOCKET;
  }

  /* If we didn't (try) to create a peer socket yet, try to make one. Don't try
   * again if the peer socket creation failed earlier for the same protocol. */
  peer_socket = loop->poll_peer_sockets[index];
  if (peer_socket == 0) {
    peer_socket = uv__fast_poll_create_peer_socket(loop->iocp, protocol_info);
    loop->poll_peer_sockets[index] = peer_socket;
  }

  return peer_socket;
}