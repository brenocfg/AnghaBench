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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telclk_interrupt ; 
 int /*<<< orphan*/  tlclk_interrupt ; 
 int /*<<< orphan*/  useflags ; 

__attribute__((used)) static int tlclk_release(struct inode *inode, struct file *filp)
{
	free_irq(telclk_interrupt, tlclk_interrupt);
	clear_bit(0, &useflags);

	return 0;
}