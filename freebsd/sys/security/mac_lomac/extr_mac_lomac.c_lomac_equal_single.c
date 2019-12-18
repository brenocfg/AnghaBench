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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_single; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 int lomac_equal_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lomac_equal_single(struct mac_lomac *a, struct mac_lomac *b)
{

	KASSERT((a->ml_flags & MAC_LOMAC_FLAG_SINGLE) != 0,
	    ("lomac_equal_single: a not single"));
	KASSERT((b->ml_flags & MAC_LOMAC_FLAG_SINGLE) != 0,
	    ("lomac_equal_single: b not single"));

	return (lomac_equal_element(&a->ml_single, &b->ml_single));
}