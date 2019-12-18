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
typedef  int /*<<< orphan*/  u8 ;
struct bt_bmc {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  bt_write (struct bt_bmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bt_writen(struct bt_bmc *bt_bmc, u8 *buf, size_t n)
{
	int i;

	for (i = 0; i < n; i++)
		bt_write(bt_bmc, buf[i]);
	return n;
}