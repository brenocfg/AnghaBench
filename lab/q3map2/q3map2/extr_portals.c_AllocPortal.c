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
typedef  int /*<<< orphan*/  portal_t ;

/* Variables and functions */
 scalar_t__ c_active_portals ; 
 scalar_t__ c_peak_portals ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numthreads ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 

portal_t *AllocPortal( void ){
	portal_t    *p;

	if ( numthreads == 1 ) {
		c_active_portals++;
	}
	if ( c_active_portals > c_peak_portals ) {
		c_peak_portals = c_active_portals;
	}

	p = safe_malloc( sizeof( portal_t ) );
	memset( p, 0, sizeof( portal_t ) );

	return p;
}