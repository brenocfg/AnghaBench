#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* items; } ;
typedef  TYPE_1__ GRawData ;

/* Variables and functions */
 scalar_t__ STRING ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_raw_data_str_value (TYPE_1__*) ; 

void
free_raw_data (GRawData * raw_data)
{
#ifdef HAVE_LIBTOKYOCABINET
  if (raw_data->type == STRING)
    free_raw_data_str_value (raw_data);
#endif
  free (raw_data->items);
  free (raw_data);
}