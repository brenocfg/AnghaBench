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
struct label {int dummy; } ;
struct ip6q {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
biba_ip6q_update(struct mbuf *m, struct label *mlabel, struct ip6q *q6,
    struct label *q6label)
{

	/* NOOP: we only accept matching labels, so no need to update */
}