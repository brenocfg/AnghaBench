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
typedef  int u_int ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_WLOCK () ; 
 int /*<<< orphan*/  IFNET_WLOCK_ASSERT () ; 
 int /*<<< orphan*/  IFNET_WUNLOCK () ; 
 int /*<<< orphan*/  M_IFNET ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int V_if_indexlim ; 
 struct ifnet** V_ifindex_table ; 
 int /*<<< orphan*/  free (struct ifnet**,int /*<<< orphan*/ ) ; 
 struct ifnet** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
if_grow(void)
{
	int oldlim;
	u_int n;
	struct ifnet **e;
	void *old;

	old = NULL;
	IFNET_WLOCK_ASSERT();
	oldlim = V_if_indexlim;
	IFNET_WUNLOCK();
	n = (oldlim << 1) * sizeof(*e);
	e = malloc(n, M_IFNET, M_WAITOK | M_ZERO);
	IFNET_WLOCK();
	if (V_if_indexlim != oldlim) {
		free(e, M_IFNET);
		return (NULL);
	}
	if (V_ifindex_table != NULL) {
		memcpy((caddr_t)e, (caddr_t)V_ifindex_table, n/2);
		old = V_ifindex_table;
	}
	V_if_indexlim <<= 1;
	V_ifindex_table = e;
	return (old);
}