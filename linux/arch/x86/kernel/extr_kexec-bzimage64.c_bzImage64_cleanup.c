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
struct bzimage64_data {int /*<<< orphan*/ * bootparams_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bzImage64_cleanup(void *loader_data)
{
	struct bzimage64_data *ldata = loader_data;

	if (!ldata)
		return 0;

	kfree(ldata->bootparams_buf);
	ldata->bootparams_buf = NULL;

	return 0;
}