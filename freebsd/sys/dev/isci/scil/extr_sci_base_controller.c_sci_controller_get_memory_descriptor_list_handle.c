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
struct TYPE_2__ {int /*<<< orphan*/  mdl; } ;
typedef  int /*<<< orphan*/  SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_CONTROLLER_T ;

/* Variables and functions */

SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T sci_controller_get_memory_descriptor_list_handle(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCI_BASE_CONTROLLER_T * this_controller = (SCI_BASE_CONTROLLER_T*)controller;
   return (SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T) &this_controller->mdl;
}