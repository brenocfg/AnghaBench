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
struct pfloghdr {int /*<<< orphan*/  af; int /*<<< orphan*/  dir; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFLOG_HDRLEN ; 
 int /*<<< orphan*/  PF_OUT ; 
 int /*<<< orphan*/  ipfw_bpf_mtap2 (struct pfloghdr*,int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static void
nat64_log(struct pfloghdr *logdata, struct mbuf *m, sa_family_t family)
{

	logdata->dir = PF_OUT;
	logdata->af = family;
	ipfw_bpf_mtap2(logdata, PFLOG_HDRLEN, m);
}