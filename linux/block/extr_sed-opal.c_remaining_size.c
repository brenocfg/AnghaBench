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
struct opal_dev {size_t pos; } ;

/* Variables and functions */
 size_t IO_BUFFER_LENGTH ; 

__attribute__((used)) static size_t remaining_size(struct opal_dev *cmd)
{
	return IO_BUFFER_LENGTH - cmd->pos;
}