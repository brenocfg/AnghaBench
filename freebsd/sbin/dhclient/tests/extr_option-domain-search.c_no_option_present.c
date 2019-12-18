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
struct packet {struct option_data* options; } ;
struct option_data {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t DHO_DOMAIN_SEARCH ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  expand_domain_search (struct packet*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 

void
no_option_present()
{
	int ret;
	struct option_data option;
	struct packet p;

	option.data = NULL;
	option.len  = 0;
	p.options[DHO_DOMAIN_SEARCH] = option;

	ret = setjmp(env);
	if (ret == 0)
		expand_domain_search(&p);

	if (p.options[DHO_DOMAIN_SEARCH].len != 0 ||
	    p.options[DHO_DOMAIN_SEARCH].data != NULL)
		abort();
}