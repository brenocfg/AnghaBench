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
typedef  void uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int const size; int const type; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ i3_ipc_header_t ;

/* Variables and functions */
 int writeall (int,void const*,int const) ; 

int ipc_send_message(int sockfd, const uint32_t message_size,
                     const uint32_t message_type, const uint8_t *payload) {
    const i3_ipc_header_t header = {
        /* We don’t use I3_IPC_MAGIC because it’s a 0-terminated C string. */
        .magic = {'i', '3', '-', 'i', 'p', 'c'},
        .size = message_size,
        .type = message_type};

    if (writeall(sockfd, ((void *)&header), sizeof(i3_ipc_header_t)) == -1)
        return -1;

    if (writeall(sockfd, payload, message_size) == -1)
        return -1;

    return 0;
}