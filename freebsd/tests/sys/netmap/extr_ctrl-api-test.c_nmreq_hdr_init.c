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
struct nmreq_header {int /*<<< orphan*/  nr_name; int /*<<< orphan*/  nr_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_API ; 
 int /*<<< orphan*/  memset (struct nmreq_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
nmreq_hdr_init(struct nmreq_header *hdr, const char *ifname)
{
	memset(hdr, 0, sizeof(*hdr));
	hdr->nr_version = NETMAP_API;
	strncpy(hdr->nr_name, ifname, sizeof(hdr->nr_name) - 1);
}