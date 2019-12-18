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
struct svc_req {int dummy; } ;

/* Variables and functions */
 void* ypproc_null_2_svc (void*,struct svc_req*) ; 

void *
ypoldproc_null_1_svc(void *argp, struct svc_req *rqstp)
{
	return(ypproc_null_2_svc(argp, rqstp));
}