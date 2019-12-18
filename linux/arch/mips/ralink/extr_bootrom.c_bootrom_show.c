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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTROM_SIZE ; 
 int /*<<< orphan*/  membase ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bootrom_show(struct seq_file *s, void *unused)
{
	seq_write(s, membase, BOOTROM_SIZE);

	return 0;
}