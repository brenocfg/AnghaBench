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
struct ber_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 struct ber_element* ldap_do_parse_search_filter (struct ber_element*,char**) ; 

__attribute__((used)) static struct ber_element *
ldap_parse_search_filter(struct ber_element *ber, char *filter)
{
	struct ber_element *elm;
	char *cp;

	cp = filter;

	if (cp == NULL || *cp == '\0') {
		errno = EINVAL;
		return (NULL);
	}

	if ((elm = ldap_do_parse_search_filter(ber, &cp)) == NULL)
		return (NULL);

	if (*cp != '\0') {
		ber_free_elements(elm);
		ber_link_elements(ber, NULL);
		errno = EINVAL;
		return (NULL);
	}

	return (elm);
}