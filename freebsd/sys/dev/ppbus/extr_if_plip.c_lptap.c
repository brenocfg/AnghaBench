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
typedef  int /*<<< orphan*/  u_int32_t ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_bpf; } ;
typedef  int /*<<< orphan*/  af ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  bpf_mtap2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct mbuf*) ; 

__attribute__((used)) static void
lptap(struct ifnet *ifp, struct mbuf *m)
{
	u_int32_t af = AF_INET;

	bpf_mtap2(ifp->if_bpf, &af, sizeof(af), m);
}