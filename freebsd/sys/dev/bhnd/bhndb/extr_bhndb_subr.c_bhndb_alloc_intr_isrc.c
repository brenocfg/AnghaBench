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
typedef  int /*<<< orphan*/  u_int ;
struct bhndb_intr_isrc {int is_rid; int /*<<< orphan*/ * is_res; int /*<<< orphan*/  is_owner; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bhndb_intr_isrc*,int /*<<< orphan*/ ) ; 
 struct bhndb_intr_isrc* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bhndb_intr_isrc *
bhndb_alloc_intr_isrc(device_t owner, int rid, rman_res_t start, rman_res_t end,
    rman_res_t count, u_int flags)
{
	struct bhndb_intr_isrc *isrc;

	isrc = malloc(sizeof(*isrc), M_BHND, M_NOWAIT);
	if (isrc == NULL)
		return (NULL);

	isrc->is_owner = owner;
	isrc->is_rid = rid;
	isrc->is_res = bus_alloc_resource(owner, SYS_RES_IRQ, &isrc->is_rid,
	    start, end, count, flags);
	if (isrc->is_res == NULL) {
		free(isrc, M_BHND);
		return (NULL);
	}

	return (isrc);
}