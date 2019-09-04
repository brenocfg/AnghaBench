#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; } ;
typedef  TYPE_1__ LabObject ;

/* Variables and functions */
#define  ENV_STATUS_INITIALIZED 129 
#define  EnvCApi_EnvironmentStatus_Running 128 

__attribute__((used)) static int is_running(LabObject* self) {
  switch (self->status) {
    case ENV_STATUS_INITIALIZED:
    case EnvCApi_EnvironmentStatus_Running:
      return true;
    default:
      return false;
  }
}