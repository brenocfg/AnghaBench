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
struct lacp_peerinfo {int /*<<< orphan*/  lip_key; int /*<<< orphan*/  lip_systemid; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lacp_peerinfo_is_compatible(const struct lacp_peerinfo *a,
    const struct lacp_peerinfo *b)
{
	if (memcmp(&a->lip_systemid, &b->lip_systemid,
	    sizeof(a->lip_systemid))) {
		return (0);
	}

	if (memcmp(&a->lip_key, &b->lip_key, sizeof(a->lip_key))) {
		return (0);
	}

	return (1);
}