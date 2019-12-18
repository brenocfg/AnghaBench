#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sl2vl; int /*<<< orphan*/  vlarb_high; int /*<<< orphan*/  vlarb_low; int /*<<< orphan*/  high_limit; int /*<<< orphan*/  max_vls; } ;
typedef  TYPE_1__ osm_qos_options_t ;

/* Variables and functions */
 int /*<<< orphan*/  subn_verify_high_limit (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  subn_verify_max_vls (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  subn_verify_sl2vl (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  subn_verify_vlarb (int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static void subn_verify_qos_set(osm_qos_options_t *set, const char *prefix)
{
	subn_verify_max_vls(&set->max_vls, prefix);
	subn_verify_high_limit(&set->high_limit, prefix);
	subn_verify_vlarb(&set->vlarb_low, prefix, "low");
	subn_verify_vlarb(&set->vlarb_high, prefix, "high");
	subn_verify_sl2vl(&set->sl2vl, prefix);
}