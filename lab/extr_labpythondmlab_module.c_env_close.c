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
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  context; TYPE_1__* env_c_api; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_context ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ LabObject ;

/* Variables and functions */
 scalar_t__ ENV_STATUS_CLOSED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int env_close(LabObject* self) {
  if (self->status != ENV_STATUS_CLOSED) {
    self->env_c_api->release_context(self->context);
    self->status = ENV_STATUS_CLOSED;
    return true;
  }
  return false;
}