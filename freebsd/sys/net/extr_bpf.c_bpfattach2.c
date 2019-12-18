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
typedef  int /*<<< orphan*/  u_int ;
struct ifnet {int dummy; } ;
struct bpf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dead_bpf_if ; 

void
bpfattach2(struct ifnet *ifp, u_int dlt, u_int hdrlen, struct bpf_if **driverp)
{

	*driverp = (struct bpf_if *)&dead_bpf_if;
}