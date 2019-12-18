#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_opensm_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_osm; } ;
typedef  TYPE_1__ lash_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static lash_t *lash_create(osm_opensm_t * p_osm)
{
	lash_t *p_lash;

	p_lash = calloc(1, sizeof(lash_t));
	if (!p_lash)
		return NULL;

	p_lash->p_osm = p_osm;

	return p_lash;
}