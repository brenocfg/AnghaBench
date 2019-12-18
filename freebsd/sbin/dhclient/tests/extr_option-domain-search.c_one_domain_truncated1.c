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
struct option_data {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t DHO_DOMAIN_SEARCH ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  expand_domain_search (struct packet*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int setjmp (int /*<<< orphan*/ ) ; 

void
one_domain_truncated1()
{
	int ret;
	struct option_data *option;
	struct packet p;

	char *data = "\007example\003org";

	option = &p.options[DHO_DOMAIN_SEARCH];
	option->len  = 12;
	option->data = malloc(option->len);
	memcpy(option->data, data, option->len);

	ret = setjmp(env);
	if (ret == 0)
		expand_domain_search(&p);

	if (ret != 1)
		abort();

	free(option->data);
}