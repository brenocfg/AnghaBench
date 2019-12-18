#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_3__ {int /*<<< orphan*/  subnetbits; int /*<<< orphan*/  addr; struct TYPE_3__* next; } ;
typedef  TYPE_1__ KeyAccT ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ keyacc_amatch (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int /*BOOL*/
keyacc_contains(
	const KeyAccT    *head,
	const sockaddr_u *addr,
	int               defv)
{
	if (head) {
		do {
			if (keyacc_amatch(&head->addr, addr,
					  head->subnetbits))
				return TRUE;
		} while (NULL != (head = head->next));
		return FALSE;
	} else {
		return !!defv;
	}
}