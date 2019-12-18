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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_vnode_label_free (struct label*) ; 

void
mac_execve_interpreter_exit(struct label *interpvplabel)
{

	if (interpvplabel != NULL)
		mac_vnode_label_free(interpvplabel);
}