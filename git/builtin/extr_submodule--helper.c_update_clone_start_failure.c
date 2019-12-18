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
struct submodule_update_clone {int quickstop; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int update_clone_start_failure(struct strbuf *err,
				      void *suc_cb,
				      void *idx_task_cb)
{
	struct submodule_update_clone *suc = suc_cb;
	suc->quickstop = 1;
	return 1;
}