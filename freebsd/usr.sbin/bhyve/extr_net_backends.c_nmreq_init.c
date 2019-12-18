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
struct nmreq {int /*<<< orphan*/  nr_version; int /*<<< orphan*/  nr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_API ; 
 int /*<<< orphan*/  memset (struct nmreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
nmreq_init(struct nmreq *req, char *ifname)
{

	memset(req, 0, sizeof(*req));
	strlcpy(req->nr_name, ifname, sizeof(req->nr_name));
	req->nr_version = NETMAP_API;
}