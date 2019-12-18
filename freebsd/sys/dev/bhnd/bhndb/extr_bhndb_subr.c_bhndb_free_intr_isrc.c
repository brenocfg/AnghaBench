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
struct bhndb_intr_isrc {int /*<<< orphan*/  is_res; int /*<<< orphan*/  is_rid; int /*<<< orphan*/  is_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bhndb_intr_isrc*,int /*<<< orphan*/ ) ; 

void
bhndb_free_intr_isrc(struct bhndb_intr_isrc *isrc)
{
	bus_release_resource(isrc->is_owner, SYS_RES_IRQ, isrc->is_rid,
	    isrc->is_res);
	free(isrc, M_BHND);
}