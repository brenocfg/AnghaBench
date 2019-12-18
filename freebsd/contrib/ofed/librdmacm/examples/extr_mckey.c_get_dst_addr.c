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
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; int /*<<< orphan*/  sib_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IB ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int get_addr (char*,struct sockaddr*) ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ib*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unmapped_addr ; 

__attribute__((used)) static int get_dst_addr(char *dst, struct sockaddr *addr)
{
	struct sockaddr_ib *sib;

	if (!unmapped_addr)
		return get_addr(dst, addr);

	sib = (struct sockaddr_ib *) addr;
	memset(sib, 0, sizeof *sib);
	sib->sib_family = AF_IB;
	inet_pton(AF_INET6, dst, &sib->sib_addr);
	return 0;
}