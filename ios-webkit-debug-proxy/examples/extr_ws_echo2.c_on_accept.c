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
typedef  int /*<<< orphan*/  sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_1__* my_sm_t ;
struct TYPE_2__ {int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM_ERROR ; 
 int /*<<< orphan*/  SM_SUCCESS ; 
 void* my_new (int,int) ; 

sm_status on_accept(sm_t sm, int server_fd, void *server_value,
    int fd, void **to_value) {
  int port = ((my_sm_t)server_value)->port;
  *to_value = my_new(fd, port);
  return (*to_value ? SM_SUCCESS : SM_ERROR);
}