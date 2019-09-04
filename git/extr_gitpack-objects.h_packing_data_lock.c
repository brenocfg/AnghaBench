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
struct packing_data {int /*<<< orphan*/  odb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void packing_data_lock(struct packing_data *pdata)
{
	pthread_mutex_lock(&pdata->odb_lock);
}