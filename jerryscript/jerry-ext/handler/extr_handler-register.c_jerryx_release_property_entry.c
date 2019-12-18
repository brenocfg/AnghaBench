#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int registered; } ;
typedef  TYPE_1__ jerryx_register_result ;
struct TYPE_6__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ jerryx_property_entry ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 

void
jerryx_release_property_entry (const jerryx_property_entry entries[], /**< list of property entries */
                               const jerryx_register_result register_result) /**< previous result of registration */
{
  for (uint32_t idx = register_result.registered;
       ((entries + idx) != NULL) && (entries[idx].name != NULL);
       idx++)
  {
    jerry_release_value (entries[idx].value);
  }
}