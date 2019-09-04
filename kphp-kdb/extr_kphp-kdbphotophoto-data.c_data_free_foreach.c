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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 

void data_free_foreach (int *a, void **v) {
  data_free (*(data **)v);
  dl_free (*(data **)v, sizeof (data));
}