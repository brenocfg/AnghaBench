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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_IFNET ; 
 int /*<<< orphan*/  MAGIC_MBUF ; 
 int /*<<< orphan*/  ifnet_create_mbuf ; 

__attribute__((used)) static void
test_ifnet_create_mbuf(struct ifnet *ifp, struct label *ifplabel,
    struct mbuf *m, struct label *mlabel)
{

	LABEL_CHECK(ifplabel, MAGIC_IFNET);
	LABEL_CHECK(mlabel, MAGIC_MBUF);
	COUNTER_INC(ifnet_create_mbuf);
}