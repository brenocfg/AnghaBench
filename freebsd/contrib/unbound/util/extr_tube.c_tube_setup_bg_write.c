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
struct tube {int /*<<< orphan*/  sw; int /*<<< orphan*/  res_com; } ;
struct comm_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_create_raw (struct comm_base*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct tube*) ; 
 int errno ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  tube_handle_write ; 

int tube_setup_bg_write(struct tube* tube, struct comm_base* base)
{
	if(!(tube->res_com = comm_point_create_raw(base, tube->sw, 
		1, tube_handle_write, tube))) {
		int err = errno;
		log_err("tube_setup_bg_w: commpoint creation failed");
		errno = err;
		return 0;
	}
	return 1;
}