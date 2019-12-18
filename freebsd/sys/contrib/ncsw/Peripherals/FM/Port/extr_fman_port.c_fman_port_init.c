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
struct fman_port_params {int dummy; } ;
struct fman_port_cfg {int dummy; } ;
struct fman_port {int type; int /*<<< orphan*/  im_en; } ;

/* Variables and functions */
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_HC 133 
#define  E_FMAN_PORT_TYPE_OP 132 
#define  E_FMAN_PORT_TYPE_RX 131 
#define  E_FMAN_PORT_TYPE_RX_10G 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int init_bmi_oh (struct fman_port*,struct fman_port_cfg*,struct fman_port_params*) ; 
 int init_bmi_rx (struct fman_port*,struct fman_port_cfg*,struct fman_port_params*) ; 
 int init_bmi_tx (struct fman_port*,struct fman_port_cfg*,struct fman_port_params*) ; 
 int init_qmi (struct fman_port*,struct fman_port_cfg*,struct fman_port_params*) ; 

int fman_port_init(struct fman_port *port,
        struct fman_port_cfg *cfg,
        struct fman_port_params *params)
{
    int err;

    /* Init BMI registers */
    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        err = init_bmi_rx(port, cfg, params);
        break;
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        err = init_bmi_tx(port, cfg, params);
        break;
    case E_FMAN_PORT_TYPE_OP:
    case E_FMAN_PORT_TYPE_HC:
        err = init_bmi_oh(port, cfg, params);
        break;
    default:
        return -EINVAL;
    }

    if (err)
        return err;

    /* Init QMI registers */
    if (!port->im_en)
    {
        err = init_qmi(port, cfg, params);
        return err;
    }
    return 0;
}