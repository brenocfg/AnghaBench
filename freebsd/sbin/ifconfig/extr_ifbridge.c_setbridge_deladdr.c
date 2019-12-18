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
struct ifbareq {int /*<<< orphan*/  ifba_dst; } ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGDADDR ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbareq*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 struct ether_addr* ether_aton (char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ifbareq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setbridge_deladdr(const char *val, int d, int s, const struct afswtch *afp)
{
	struct ifbareq req;
	struct ether_addr *ea;

	memset(&req, 0, sizeof(req));

	ea = ether_aton(val);
	if (ea == NULL)
		errx(1, "invalid address: %s",  val);

	memcpy(req.ifba_dst, ea->octet, sizeof(req.ifba_dst));

	if (do_cmd(s, BRDGDADDR, &req, sizeof(req), 1) < 0)
		err(1, "BRDGDADDR %s",  val);
}