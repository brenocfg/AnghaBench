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
struct TYPE_4__ {int new_ids_n; int /*<<< orphan*/  new_local_ids; int /*<<< orphan*/  new_ids; } ;
typedef  TYPE_1__ data_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void data_iterator_free (data_iterator *it) {
  dl_free (it->new_ids, sizeof (int) * it->new_ids_n);
  dl_free (it->new_local_ids, sizeof (int) * it->new_ids_n);
  memset (it, 0, sizeof (*it));
}