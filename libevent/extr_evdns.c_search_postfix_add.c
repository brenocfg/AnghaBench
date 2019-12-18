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
typedef  int /*<<< orphan*/  u8 ;
struct search_domain {int len; struct search_domain* next; } ;
struct evdns_base {TYPE_1__* global_search_state; } ;
struct TYPE_2__ {struct search_domain* head; int /*<<< orphan*/  num_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ mm_malloc (int) ; 
 TYPE_1__* search_state_new () ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
search_postfix_add(struct evdns_base *base, const char *domain) {
	size_t domain_len;
	struct search_domain *sdomain;
	while (domain[0] == '.') domain++;
	domain_len = strlen(domain);

	ASSERT_LOCKED(base);
	if (!base->global_search_state) base->global_search_state = search_state_new();
	if (!base->global_search_state) return;
	base->global_search_state->num_domains++;

	sdomain = (struct search_domain *) mm_malloc(sizeof(struct search_domain) + domain_len);
	if (!sdomain) return;
	memcpy( ((u8 *) sdomain) + sizeof(struct search_domain), domain, domain_len);
	sdomain->next = base->global_search_state->head;
	sdomain->len = (int) domain_len;

	base->global_search_state->head = sdomain;
}