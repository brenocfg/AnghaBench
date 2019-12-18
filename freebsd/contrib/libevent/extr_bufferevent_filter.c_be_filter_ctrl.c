#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union bufferevent_ctrl_data {TYPE_2__* ptr; } ;
struct bufferevent_filtered {TYPE_2__* underlying; } ;
struct bufferevent {int dummy; } ;
typedef  enum bufferevent_ctrl_op { ____Placeholder_bufferevent_ctrl_op } bufferevent_ctrl_op ;
struct TYPE_4__ {TYPE_1__* be_ops; } ;
struct TYPE_3__ {int (* ctrl ) (TYPE_2__*,int,union bufferevent_ctrl_data*) ;} ;

/* Variables and functions */
#define  BEV_CTRL_CANCEL_ALL 131 
#define  BEV_CTRL_GET_FD 130 
#define  BEV_CTRL_GET_UNDERLYING 129 
#define  BEV_CTRL_SET_FD 128 
 int stub1 (TYPE_2__*,int,union bufferevent_ctrl_data*) ; 
 struct bufferevent_filtered* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_filter_ctrl(struct bufferevent *bev, enum bufferevent_ctrl_op op,
    union bufferevent_ctrl_data *data)
{
	struct bufferevent_filtered *bevf;
	switch (op) {
	case BEV_CTRL_GET_UNDERLYING:
		bevf = upcast(bev);
		data->ptr = bevf->underlying;
		return 0;
	case BEV_CTRL_SET_FD:
		bevf = upcast(bev);

		if (bevf->underlying &&
			bevf->underlying->be_ops &&
			bevf->underlying->be_ops->ctrl) {
		    return (bevf->underlying->be_ops->ctrl)(bevf->underlying, op, data);
		}

	case BEV_CTRL_GET_FD:
	case BEV_CTRL_CANCEL_ALL:
	default:
		return -1;
	}

	return -1;
}