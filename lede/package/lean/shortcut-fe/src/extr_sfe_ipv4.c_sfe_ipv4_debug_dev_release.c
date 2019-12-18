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
struct sfe_ipv4_debug_xml_write_state {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sfe_ipv4_debug_xml_write_state*) ; 

__attribute__((used)) static int sfe_ipv4_debug_dev_release(struct inode *inode, struct file *file)
{
	struct sfe_ipv4_debug_xml_write_state *ws;

	ws = (struct sfe_ipv4_debug_xml_write_state *)file->private_data;
	if (ws) {
		/*
		 * We've finished with our output so free the write state.
		 */
		kfree(ws);
	}

	return 0;
}