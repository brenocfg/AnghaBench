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
struct si_sm_data {size_t write_pos; int /*<<< orphan*/  write_count; int /*<<< orphan*/ * write_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_data (struct si_sm_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_next_byte(struct si_sm_data *kcs)
{
	write_data(kcs, kcs->write_data[kcs->write_pos]);
	(kcs->write_pos)++;
	(kcs->write_count)--;
}