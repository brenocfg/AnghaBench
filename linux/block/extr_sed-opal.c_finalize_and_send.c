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
struct opal_dev {int /*<<< orphan*/  pos; int /*<<< orphan*/  cmd; int /*<<< orphan*/  tsn; int /*<<< orphan*/  hsn; } ;
typedef  int /*<<< orphan*/  cont_fn ;

/* Variables and functions */
 int cmd_finalize (struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opal_send_recv (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  print_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int finalize_and_send(struct opal_dev *dev, cont_fn cont)
{
	int ret;

	ret = cmd_finalize(dev, dev->hsn, dev->tsn);
	if (ret) {
		pr_debug("Error finalizing command buffer: %d\n", ret);
		return ret;
	}

	print_buffer(dev->cmd, dev->pos);

	return opal_send_recv(dev, cont);
}