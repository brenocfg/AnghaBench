#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GRawData ;
typedef  size_t GModule ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 scalar_t__ holder ; 
 int /*<<< orphan*/  load_holder_data (int /*<<< orphan*/ *,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * module_sort ; 
 int /*<<< orphan*/ * parse_raw_data (size_t) ; 

__attribute__((used)) static void
allocate_holder_by_module (GModule module)
{
  GRawData *raw_data;

  /* extract data from the corresponding hash table */
  raw_data = parse_raw_data (module);
  if (!raw_data) {
    LOG_DEBUG (("raw data is NULL for module: %d.\n", module));
    return;
  }

  load_holder_data (raw_data, holder + module, module, module_sort[module]);
}