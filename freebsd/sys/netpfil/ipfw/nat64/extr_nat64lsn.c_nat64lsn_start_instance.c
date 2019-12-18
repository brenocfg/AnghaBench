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
struct nat64lsn_cfg {int /*<<< orphan*/  periodic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_LOCK (struct nat64lsn_cfg*) ; 
 int /*<<< orphan*/  CALLOUT_UNLOCK (struct nat64lsn_cfg*) ; 
 int PERIODIC_DELAY ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nat64lsn_cfg*) ; 
 int hz ; 
 int /*<<< orphan*/  nat64lsn_periodic ; 

void
nat64lsn_start_instance(struct nat64lsn_cfg *cfg)
{

	CALLOUT_LOCK(cfg);
	callout_reset(&cfg->periodic, hz * PERIODIC_DELAY,
	    nat64lsn_periodic, cfg);
	CALLOUT_UNLOCK(cfg);
}