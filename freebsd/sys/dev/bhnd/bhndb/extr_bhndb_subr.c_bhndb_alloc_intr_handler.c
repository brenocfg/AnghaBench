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
struct resource {int dummy; } ;
struct bhndb_intr_isrc {int dummy; } ;
struct bhndb_intr_handler {int ih_active; int /*<<< orphan*/ * ih_cookiep; struct bhndb_intr_isrc* ih_isrc; struct resource* ih_res; int /*<<< orphan*/  ih_owner; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct bhndb_intr_handler* malloc (int,int /*<<< orphan*/ ,int) ; 

struct bhndb_intr_handler *
bhndb_alloc_intr_handler(device_t owner, struct resource *r,
    struct bhndb_intr_isrc *isrc)
{
	struct bhndb_intr_handler *ih;

	ih = malloc(sizeof(*ih), M_BHND, M_NOWAIT | M_ZERO);
	ih->ih_owner = owner;
	ih->ih_res = r;
	ih->ih_isrc = isrc;
	ih->ih_cookiep = NULL;
	ih->ih_active = false;

	return (ih);
}