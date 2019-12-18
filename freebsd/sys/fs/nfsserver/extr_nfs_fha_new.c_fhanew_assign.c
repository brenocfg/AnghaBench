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
typedef  int /*<<< orphan*/  SVCTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/ * fha_assign (int /*<<< orphan*/ *,struct svc_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fhanew_softc ; 

SVCTHREAD *
fhanew_assign(SVCTHREAD *this_thread, struct svc_req *req)
{
	return (fha_assign(this_thread, req, &fhanew_softc));
}