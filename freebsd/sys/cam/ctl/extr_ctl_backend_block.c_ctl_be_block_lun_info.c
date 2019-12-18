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
struct sbuf {int dummy; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  num_threads; } ;

/* Variables and functions */
 int sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static int
ctl_be_block_lun_info(void *be_lun, struct sbuf *sb)
{
	struct ctl_be_block_lun *lun;
	int retval;

	lun = (struct ctl_be_block_lun *)be_lun;

	retval = sbuf_printf(sb, "\t<num_threads>");
	if (retval != 0)
		goto bailout;
	retval = sbuf_printf(sb, "%d", lun->num_threads);
	if (retval != 0)
		goto bailout;
	retval = sbuf_printf(sb, "</num_threads>\n");

bailout:
	return (retval);
}