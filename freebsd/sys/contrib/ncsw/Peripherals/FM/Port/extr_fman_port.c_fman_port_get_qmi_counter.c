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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {int dummy; } ;
typedef  enum fman_port_qmi_counters { ____Placeholder_fman_port_qmi_counters } fman_port_qmi_counters ;

/* Variables and functions */
 int /*<<< orphan*/  get_qmi_counter_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_port_get_qmi_counter(struct fman_port *port,
        enum fman_port_qmi_counters  counter)
{
    uint32_t *queue_reg, ret_val;

    get_qmi_counter_reg(port, counter, &queue_reg);

    if (queue_reg == NULL)
        return 0;

    ret_val = ioread32be(queue_reg);
    return ret_val;
}