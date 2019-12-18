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
typedef  int u_long ;
struct sioc_sg_req6 {int dummy; } ;
struct sioc_mif_req6 {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SIOCGETMIFCNT_IN6 129 
#define  SIOCGETSGCNT_IN6 128 
 int get_mif6_cnt (struct sioc_mif_req6*) ; 
 int get_sg_cnt (struct sioc_sg_req6*) ; 

int
X_mrt6_ioctl(u_long cmd, caddr_t data)
{
	int ret;

	ret = EINVAL;

	switch (cmd) {
	case SIOCGETSGCNT_IN6:
		ret = get_sg_cnt((struct sioc_sg_req6 *)data);
		break;

	case SIOCGETMIFCNT_IN6:
		ret = get_mif6_cnt((struct sioc_mif_req6 *)data);
		break;

	default:
		break;
	}

	return (ret);
}