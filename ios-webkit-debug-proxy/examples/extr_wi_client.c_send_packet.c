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
typedef  TYPE_1__* wi_t ;
typedef  int /*<<< orphan*/  wi_status ;
typedef  size_t ssize_t ;
typedef  TYPE_2__* my_wi_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WI_ERROR ; 
 int /*<<< orphan*/  WI_SUCCESS ; 
 size_t send (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

wi_status send_packet(wi_t wi, const char *packet, size_t length) {
  my_wi_t my_wi = (my_wi_t)wi->state;
  ssize_t sent_bytes = send(my_wi->fd, (void*)packet, length, 0);
  return (sent_bytes == length ? WI_SUCCESS : WI_ERROR);
}