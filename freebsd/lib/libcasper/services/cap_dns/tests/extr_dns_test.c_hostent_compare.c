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
struct hostent {scalar_t__ h_addrtype; scalar_t__ h_length; int /*<<< orphan*/  h_addr_list; int /*<<< orphan*/  h_aliases; int /*<<< orphan*/ * h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostent_addr_list_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hostent_aliases_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
hostent_compare(const struct hostent *hp0, const struct hostent *hp1)
{

	if (hp0 == NULL && hp1 != NULL)
		return (true);

	if (hp0 == NULL || hp1 == NULL)
		return (false);

	if (hp0->h_name != NULL || hp1->h_name != NULL) {
		if (hp0->h_name == NULL || hp1->h_name == NULL)
			return (false);
		if (strcmp(hp0->h_name, hp1->h_name) != 0)
			return (false);
	}

	if (!hostent_aliases_compare(hp0->h_aliases, hp1->h_aliases))
		return (false);
	if (!hostent_aliases_compare(hp1->h_aliases, hp0->h_aliases))
		return (false);

	if (hp0->h_addrtype != hp1->h_addrtype)
		return (false);

	if (hp0->h_length != hp1->h_length)
		return (false);

	if (!hostent_addr_list_compare(hp0->h_addr_list, hp1->h_addr_list,
	    hp0->h_length)) {
		return (false);
	}
	if (!hostent_addr_list_compare(hp1->h_addr_list, hp0->h_addr_list,
	    hp0->h_length)) {
		return (false);
	}

	return (true);
}