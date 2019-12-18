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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pfsync_header {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ PFSYNC_HDRLEN ; 
 int /*<<< orphan*/  pfsync_print (int /*<<< orphan*/ *,struct pfsync_header*,int /*<<< orphan*/  const*,scalar_t__) ; 

void
pfsync_ip_print(netdissect_options *ndo , const u_char *bp, u_int len)
{
	struct pfsync_header *hdr = (struct pfsync_header *)bp;

	if (len < PFSYNC_HDRLEN)
		ND_PRINT((ndo, "[|pfsync]"));
	else
		pfsync_print(ndo, hdr, bp + sizeof(struct pfsync_header),
		    len - sizeof(struct pfsync_header));
}