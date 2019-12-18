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
struct ifbreq {int /*<<< orphan*/  ifbr_ifsflags; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGFLUSH ; 
 int /*<<< orphan*/  IFBF_FLUSHDYN ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbreq*,int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memset (struct ifbreq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setbridge_flush(const char *val, int d, int s, const struct afswtch *afp)
{
	struct ifbreq req;

	memset(&req, 0, sizeof(req));
	req.ifbr_ifsflags = IFBF_FLUSHDYN;
	if (do_cmd(s, BRDGFLUSH, &req, sizeof(req), 1) < 0)
		err(1, "BRDGFLUSH");
}