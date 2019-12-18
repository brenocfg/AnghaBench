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
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;
struct ip6q {int dummy; } ;

/* Variables and functions */
 struct mac_mls* SLOT (struct label*) ; 
 int mls_equal_effective (struct mac_mls*,struct mac_mls*) ; 

__attribute__((used)) static int
mls_ip6q_match(struct mbuf *m, struct label *mlabel, struct ip6q *q6,
    struct label *q6label)
{
	struct mac_mls *a, *b;

	a = SLOT(q6label);
	b = SLOT(mlabel);

	return (mls_equal_effective(a, b));
}