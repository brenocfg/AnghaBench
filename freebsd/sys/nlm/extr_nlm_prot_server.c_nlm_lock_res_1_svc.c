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
typedef  int /*<<< orphan*/  nlm_res ;
typedef  int /*<<< orphan*/  nlm4_res ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  nlm4_lock_res_4_svc (int /*<<< orphan*/ *,void*,struct svc_req*) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_res (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
nlm_lock_res_1_svc(nlm_res *argp, void *result, struct svc_req *rqstp)
{
	nlm4_res arg4;

	nlm_convert_to_nlm4_res(&arg4, argp);
	return (nlm4_lock_res_4_svc(&arg4, result, rqstp));
}