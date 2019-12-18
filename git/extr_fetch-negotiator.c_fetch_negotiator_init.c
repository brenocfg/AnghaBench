#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fetch_negotiation_algorithm; } ;
struct repository {TYPE_1__ settings; } ;
struct fetch_negotiator {int dummy; } ;

/* Variables and functions */
#define  FETCH_NEGOTIATION_DEFAULT 129 
#define  FETCH_NEGOTIATION_SKIPPING 128 
 int /*<<< orphan*/  default_negotiator_init (struct fetch_negotiator*) ; 
 int /*<<< orphan*/  prepare_repo_settings (struct repository*) ; 
 int /*<<< orphan*/  skipping_negotiator_init (struct fetch_negotiator*) ; 

void fetch_negotiator_init(struct repository *r,
			   struct fetch_negotiator *negotiator)
{
	prepare_repo_settings(r);
	switch(r->settings.fetch_negotiation_algorithm) {
	case FETCH_NEGOTIATION_SKIPPING:
		skipping_negotiator_init(negotiator);
		return;

	case FETCH_NEGOTIATION_DEFAULT:
	default:
		default_negotiator_init(negotiator);
		return;
	}
}