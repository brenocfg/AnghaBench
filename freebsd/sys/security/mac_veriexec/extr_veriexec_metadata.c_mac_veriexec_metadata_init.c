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

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ve_mutex ; 
 int /*<<< orphan*/  veriexec_dev_head ; 
 int /*<<< orphan*/  veriexec_file_dev_head ; 

void
mac_veriexec_metadata_init(void)
{

	mtx_init(&ve_mutex, "veriexec lock", NULL, MTX_DEF);
	LIST_INIT(&veriexec_dev_head);
	LIST_INIT(&veriexec_file_dev_head);
}