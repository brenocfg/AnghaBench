#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  items; int /*<<< orphan*/  size; int /*<<< orphan*/  module; scalar_t__ idx; } ;
typedef  TYPE_1__ GRawData ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 TYPE_1__* new_grawdata () ; 
 int /*<<< orphan*/  new_grawdata_item (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GRawData *
init_new_raw_data (GModule module, uint32_t ht_size)
{
  GRawData *raw_data;

  raw_data = new_grawdata ();
  raw_data->idx = 0;
  raw_data->module = module;
  raw_data->size = ht_size;
  raw_data->items = new_grawdata_item (ht_size);

  return raw_data;
}