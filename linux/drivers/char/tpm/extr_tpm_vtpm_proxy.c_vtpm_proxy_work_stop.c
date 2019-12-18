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
struct proxy_dev {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpm_proxy_fops_undo_open (struct proxy_dev*) ; 

__attribute__((used)) static void vtpm_proxy_work_stop(struct proxy_dev *proxy_dev)
{
	vtpm_proxy_fops_undo_open(proxy_dev);
	flush_work(&proxy_dev->work);
}