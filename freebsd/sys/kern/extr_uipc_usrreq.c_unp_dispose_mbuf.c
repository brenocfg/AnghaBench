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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unp_freerights ; 
 int /*<<< orphan*/  unp_scan (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unp_dispose_mbuf(struct mbuf *m)
{

	if (m)
		unp_scan(m, unp_freerights);
}