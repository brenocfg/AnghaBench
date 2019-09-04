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
struct fetch_negotiator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_negotiator_init (struct fetch_negotiator*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  skipping_negotiator_init (struct fetch_negotiator*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void fetch_negotiator_init(struct fetch_negotiator *negotiator,
			   const char *algorithm)
{
	if (algorithm) {
		if (!strcmp(algorithm, "skipping")) {
			skipping_negotiator_init(negotiator);
			return;
		} else if (!strcmp(algorithm, "default")) {
			/* Fall through to default initialization */
		} else {
			die("unknown fetch negotiation algorithm '%s'", algorithm);
		}
	}
	default_negotiator_init(negotiator);
}