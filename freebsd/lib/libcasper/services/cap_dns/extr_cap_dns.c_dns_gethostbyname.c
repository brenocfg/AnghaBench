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
struct hostent {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int NO_RECOVERY ; 
 int /*<<< orphan*/  dns_allowed_family (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dns_allowed_type (int /*<<< orphan*/  const*,char*) ; 
 struct hostent* gethostbyname2 (int /*<<< orphan*/ ,int) ; 
 int h_errno ; 
 int /*<<< orphan*/  hostent_pack (struct hostent*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int
dns_gethostbyname(const nvlist_t *limits, const nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	struct hostent *hp;
	int family;

	if (!dns_allowed_type(limits, "NAME2ADDR") &&
	    !dns_allowed_type(limits, "NAME"))
		return (NO_RECOVERY);

	family = (int)nvlist_get_number(nvlin, "family");

	if (!dns_allowed_family(limits, family))
		return (NO_RECOVERY);

	hp = gethostbyname2(nvlist_get_string(nvlin, "name"), family);
	if (hp == NULL)
		return (h_errno);
	hostent_pack(hp, nvlout);
	return (0);
}