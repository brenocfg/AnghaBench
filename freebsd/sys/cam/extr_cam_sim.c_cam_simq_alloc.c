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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cam_devq {int dummy; } ;

/* Variables and functions */
 struct cam_devq* cam_devq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct cam_devq *
cam_simq_alloc(u_int32_t max_sim_transactions)
{
	return (cam_devq_alloc(/*size*/0, max_sim_transactions));
}