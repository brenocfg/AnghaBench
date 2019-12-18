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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
#define  CLCR_GET_LOWVERS 131 
#define  CLCR_GET_RPCB_TIMEOUT 130 
#define  CLCR_SET_LOWVERS 129 
#define  CLCR_SET_RPCB_TIMEOUT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int __rpc_lowvers ; 
 struct timeval tottimeout ; 

bool_t
__rpc_control(int request, void *info)
{
	switch (request) {
	case CLCR_GET_RPCB_TIMEOUT:
		*(struct timeval *)info = tottimeout;
		break;
	case CLCR_SET_RPCB_TIMEOUT:
		tottimeout = *(struct timeval *)info;
		break;
	case CLCR_SET_LOWVERS:
		__rpc_lowvers = *(int *)info;
		break;
	case CLCR_GET_LOWVERS:
		*(int *)info = __rpc_lowvers;
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}