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
struct TYPE_2__ {int attack_mode; int hash_mode; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ tuning_db_entry_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sort_by_tuning_db_entry (const void *v1, const void *v2)
{
  const tuning_db_entry_t *t1 = (const tuning_db_entry_t *) v1;
  const tuning_db_entry_t *t2 = (const tuning_db_entry_t *) v2;

  const int res1 = strcmp (t1->device_name, t2->device_name);

  if (res1 != 0) return (res1);

  const int res2 = t1->attack_mode
                 - t2->attack_mode;

  if (res2 != 0) return (res2);

  const int res3 = t1->hash_mode
                 - t2->hash_mode;

  if (res3 != 0) return (res3);

  return 0;
}