#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  idx; } ;
typedef  scalar_t__ GRawDataType ;
typedef  TYPE_1__ GRawData ;
typedef  int GModule ;

/* Variables and functions */
 scalar_t__ INTEGER ; 
 int /*<<< orphan*/  MTRC_DATAMAP ; 
 int /*<<< orphan*/  MTRC_HITS ; 
 scalar_t__ STRING ; 
#define  VISITORS 128 
 int /*<<< orphan*/  data_iter_generic ; 
 void* get_hash (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_get_size (void*) ; 
 TYPE_1__* init_new_raw_data (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_raw_num_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_raw_str_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_db_foreach (void*,int /*<<< orphan*/ ,TYPE_1__*) ; 

GRawData *
parse_raw_data (GModule module)
{
  GRawData *raw_data;
  GRawDataType type;
  uint32_t ht_size = 0;
  void *hash = NULL;

  switch (module) {
  case VISITORS:
    hash = get_hash (module, MTRC_DATAMAP);
    type = STRING;
    break;
  default:
    hash = get_hash (module, MTRC_HITS);
    type = INTEGER;
  }

  if (!hash)
    return NULL;

  ht_size = ht_get_size (hash);
  raw_data = init_new_raw_data (module, ht_size);
  raw_data->type = type;

  tc_db_foreach (hash, data_iter_generic, raw_data);
  if (raw_data->type == STRING) {
    sort_raw_str_data (raw_data, raw_data->idx);
  } else {
    sort_raw_num_data (raw_data, raw_data->idx);
  }

  return raw_data;
}