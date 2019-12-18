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
struct ifbareq {int ifba_vlan; int /*<<< orphan*/  ifba_flags; int /*<<< orphan*/  ifba_dst; int /*<<< orphan*/  ifba_ifsname; } ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSADDR ; 
 int /*<<< orphan*/  IFBAF_STATIC ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbareq*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 struct ether_addr* ether_aton (char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ifbareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
setbridge_static(const char *val, const char *mac, int s,
    const struct afswtch *afp)
{
	struct ifbareq req;
	struct ether_addr *ea;

	memset(&req, 0, sizeof(req));
	strlcpy(req.ifba_ifsname, val, sizeof(req.ifba_ifsname));

	ea = ether_aton(mac);
	if (ea == NULL)
		errx(1, "%s: invalid address: %s", val, mac);

	memcpy(req.ifba_dst, ea->octet, sizeof(req.ifba_dst));
	req.ifba_flags = IFBAF_STATIC;
	req.ifba_vlan = 1; /* XXX allow user to specify */

	if (do_cmd(s, BRDGSADDR, &req, sizeof(req), 1) < 0)
		err(1, "BRDGSADDR %s",  val);
}