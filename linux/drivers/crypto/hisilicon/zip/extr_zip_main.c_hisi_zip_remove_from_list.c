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
struct hisi_zip {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_zip_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hisi_zip_remove_from_list(struct hisi_zip *hisi_zip)
{
	mutex_lock(&hisi_zip_list_lock);
	list_del(&hisi_zip->list);
	mutex_unlock(&hisi_zip_list_lock);
}