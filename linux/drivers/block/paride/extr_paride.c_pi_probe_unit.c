#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int unit; TYPE_1__* proto; } ;
struct TYPE_11__ {int max_units; int (* test_port ) (TYPE_2__*) ;int max_mode; scalar_t__ (* probe_unit ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  pi_claim (TYPE_2__*) ; 
 scalar_t__ pi_probe_mode (TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  pi_register_parport (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pi_unclaim (TYPE_2__*) ; 
 int /*<<< orphan*/  pi_unregister_parport (TYPE_2__*) ; 
 int stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_2__*) ; 

__attribute__((used)) static int pi_probe_unit(PIA * pi, int unit, char *scratch, int verbose)
{
	int max, s, e;

	s = unit;
	e = s + 1;

	if (s == -1) {
		s = 0;
		e = pi->proto->max_units;
	}

	if (!pi_register_parport(pi, verbose, s))
		return 0;

	if (pi->proto->test_port) {
		pi_claim(pi);
		max = pi->proto->test_port(pi);
		pi_unclaim(pi);
	} else
		max = pi->proto->max_mode;

	if (pi->proto->probe_unit) {
		pi_claim(pi);
		for (pi->unit = s; pi->unit < e; pi->unit++)
			if (pi->proto->probe_unit(pi)) {
				pi_unclaim(pi);
				if (pi_probe_mode(pi, max, scratch, verbose))
					return 1;
				pi_unregister_parport(pi);
				return 0;
			}
		pi_unclaim(pi);
		pi_unregister_parport(pi);
		return 0;
	}

	if (!pi_probe_mode(pi, max, scratch, verbose)) {
		pi_unregister_parport(pi);
		return 0;
	}
	return 1;

}