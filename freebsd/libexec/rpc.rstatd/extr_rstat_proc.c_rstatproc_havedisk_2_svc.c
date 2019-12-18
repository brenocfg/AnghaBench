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
typedef  int /*<<< orphan*/  u_int ;
struct svc_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * rstatproc_havedisk_3_svc (void*,struct svc_req*) ; 

u_int *
rstatproc_havedisk_2_svc(void *argp, struct svc_req *rqstp)
{
    return(rstatproc_havedisk_3_svc(argp, rqstp));
}