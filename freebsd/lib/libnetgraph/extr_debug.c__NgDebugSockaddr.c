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
struct sockaddr_ng {int /*<<< orphan*/  sg_data; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGLOGX (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_NgDebugSockaddr(const struct sockaddr_ng *sg)
{
	NGLOGX("SOCKADDR: { fam=%d len=%d addr=\"%s\" }",
	       sg->sg_family, sg->sg_len, sg->sg_data);
}