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
struct mac_lomac {int ml_flags; } ;

/* Variables and functions */
 int MAC_LOMAC_FLAG_SINGLE ; 
 int /*<<< orphan*/  bzero (struct mac_lomac*,int) ; 
 int /*<<< orphan*/  lomac_copy (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static void
try_relabel(struct mac_lomac *from, struct mac_lomac *to)
{

	if (from->ml_flags & MAC_LOMAC_FLAG_SINGLE) {
		bzero(to, sizeof(*to));
		lomac_copy(from, to);
	}
}