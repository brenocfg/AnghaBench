#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_slaves_pport {int /*<<< orphan*/  slaves; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
typedef  enum slave_port_gen_event { ____Placeholder_slave_port_gen_event } slave_port_gen_event ;
struct TYPE_2__ {int num_vfs; } ;

/* Variables and functions */
 struct mlx4_slaves_pport mlx4_phys_to_slaves_pport (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_and_calc_slave_port_state (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_all_slave_state(struct mlx4_dev *dev, u8 port, int event)
{
	int i;
	enum slave_port_gen_event gen_event;
	struct mlx4_slaves_pport slaves_pport = mlx4_phys_to_slaves_pport(dev,
									  port);

	for (i = 0; i < dev->persist->num_vfs + 1; i++)
		if (test_bit(i, slaves_pport.slaves))
			set_and_calc_slave_port_state(dev, i, port,
						      event, &gen_event);
}