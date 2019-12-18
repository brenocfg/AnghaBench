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
struct TYPE_3__ {int idx; scalar_t__ sub_items_size; scalar_t__ holder_size; int /*<<< orphan*/ * items; } ;
typedef  size_t GModule ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_holder_data (int /*<<< orphan*/ ) ; 

void
free_holder_by_module (GHolder ** holder, GModule module)
{
  int j;

  if ((*holder) == NULL)
    return;

  for (j = 0; j < (*holder)[module].idx; j++) {
    free_holder_data ((*holder)[module].items[j]);
  }
  free ((*holder)[module].items);

  (*holder)[module].holder_size = 0;
  (*holder)[module].idx = 0;
  (*holder)[module].sub_items_size = 0;
}