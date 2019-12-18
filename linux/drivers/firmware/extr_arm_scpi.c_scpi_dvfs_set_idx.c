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
struct dvfs_set {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  stat ;
typedef  int /*<<< orphan*/  dvfs ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_DVFS ; 
 int scpi_send_message (int /*<<< orphan*/ ,struct dvfs_set*,int,int*,int) ; 

__attribute__((used)) static int scpi_dvfs_set_idx(u8 domain, u8 index)
{
	int stat;
	struct dvfs_set dvfs = {domain, index};

	return scpi_send_message(CMD_SET_DVFS, &dvfs, sizeof(dvfs),
				 &stat, sizeof(stat));
}