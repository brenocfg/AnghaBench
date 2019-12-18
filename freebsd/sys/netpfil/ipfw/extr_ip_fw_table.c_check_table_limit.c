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
struct tentry_info {int flags; } ;
struct table_config {scalar_t__ limit; scalar_t__ count; } ;

/* Variables and functions */
 int EFBIG ; 
 int TEI_FLAGS_DONTADD ; 
 int TEI_FLAGS_LIMIT ; 
 int TEI_FLAGS_UPDATE ; 

__attribute__((used)) static int
check_table_limit(struct table_config *tc, struct tentry_info *tei)
{

	if (tc->limit == 0 || tc->count < tc->limit)
		return (0);

	if ((tei->flags & TEI_FLAGS_UPDATE) == 0) {
		/* Notify userland on error cause */
		tei->flags |= TEI_FLAGS_LIMIT;
		return (EFBIG);
	}

	/*
	 * We have UPDATE flag set.
	 * Permit updating record (if found),
	 * but restrict adding new one since we've
	 * already hit the limit.
	 */
	tei->flags |= TEI_FLAGS_DONTADD;

	return (0);
}