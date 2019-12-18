#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat; } ;
typedef  TYPE_1__ nlm4_shareres ;
typedef  int /*<<< orphan*/  nlm4_shareargs ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm4_denied ; 

bool_t
nlm4_unshare_4_svc(nlm4_shareargs *argp, nlm4_shareres *result, struct svc_req *rqstp)
{

	memset(result, 0, sizeof(*result));
	result->stat = nlm4_denied;
	return (TRUE);
}