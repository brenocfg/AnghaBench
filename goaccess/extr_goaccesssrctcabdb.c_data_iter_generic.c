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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  TCADB ;
typedef  TYPE_1__ GRawData ;

/* Variables and functions */
 scalar_t__ STRING ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  set_raw_data (void*,void*,TYPE_1__*) ; 
 void* tcadbget (int /*<<< orphan*/ *,void*,int,int*) ; 

__attribute__((used)) static void
data_iter_generic (TCADB * adb, void *key, int ksize, void *user_data)
{
  GRawData *raw_data = user_data;
  void *value;
  int sp = 0;

  value = tcadbget (adb, key, ksize, &sp);
  if (value) {
    set_raw_data (key, value, raw_data);
    if (raw_data->type != STRING)
      free (value);
  }
}