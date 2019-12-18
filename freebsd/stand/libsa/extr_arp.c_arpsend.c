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
struct iodesc {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_ARP ; 
 int /*<<< orphan*/  bcea ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sendether (struct iodesc*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
arpsend(struct iodesc *d, void *pkt, size_t len)
{

#ifdef ARP_DEBUG
 	if (debug)
		printf("arpsend: called\n");
#endif

	return (sendether(d, pkt, len, bcea, ETHERTYPE_ARP));
}