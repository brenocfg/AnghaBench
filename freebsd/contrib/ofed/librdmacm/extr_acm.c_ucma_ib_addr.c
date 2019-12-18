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
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ AF_IB ; 

__attribute__((used)) static int ucma_ib_addr(struct sockaddr *addr, socklen_t len)
{
	return len && addr && (addr->sa_family == AF_IB);
}