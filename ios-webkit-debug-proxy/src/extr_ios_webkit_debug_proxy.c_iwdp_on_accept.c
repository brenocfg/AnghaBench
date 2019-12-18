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
typedef  TYPE_1__* iwdp_type_t ;
typedef  TYPE_2__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  int /*<<< orphan*/  iwdp_iws_t ;
typedef  int /*<<< orphan*/  iwdp_iport_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* on_error ) (TYPE_2__*,char*,int) ;} ;
struct TYPE_6__ {int type; } ;

/* Variables and functions */
 int TYPE_IPORT ; 
 int /*<<< orphan*/  iwdp_iport_accept (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int) ; 

iwdp_status iwdp_on_accept(iwdp_t self, int s_fd, void *value,
    int fd, void **to_value) {
  int type = ((iwdp_type_t)value)->type;
  if (type == TYPE_IPORT) {
    return iwdp_iport_accept(self, (iwdp_iport_t)value, fd,
        (iwdp_iws_t*)to_value);
  } else {
    return self->on_error(self, "Unexpected accept type %d", type);
  }
}