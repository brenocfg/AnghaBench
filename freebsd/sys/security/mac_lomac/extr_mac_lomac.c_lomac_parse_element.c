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
struct mac_lomac_element {int mle_grade; int /*<<< orphan*/  mle_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_LOMAC_TYPE_EQUAL ; 
 int /*<<< orphan*/  MAC_LOMAC_TYPE_GRADE ; 
 int /*<<< orphan*/  MAC_LOMAC_TYPE_HIGH ; 
 int /*<<< orphan*/  MAC_LOMAC_TYPE_LOW ; 
 void* MAC_LOMAC_TYPE_UNDEF ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
lomac_parse_element(struct mac_lomac_element *element, char *string)
{

	if (strcmp(string, "high") == 0 || strcmp(string, "hi") == 0) {
		element->mle_type = MAC_LOMAC_TYPE_HIGH;
		element->mle_grade = MAC_LOMAC_TYPE_UNDEF;
	} else if (strcmp(string, "low") == 0 || strcmp(string, "lo") == 0) {
		element->mle_type = MAC_LOMAC_TYPE_LOW;
		element->mle_grade = MAC_LOMAC_TYPE_UNDEF;
	} else if (strcmp(string, "equal") == 0 ||
	    strcmp(string, "eq") == 0) {
		element->mle_type = MAC_LOMAC_TYPE_EQUAL;
		element->mle_grade = MAC_LOMAC_TYPE_UNDEF;
	} else {
		char *p0, *p1;
		int d;

		p0 = string;
		d = strtol(p0, &p1, 10);
	
		if (d < 0 || d > 65535)
			return (EINVAL);
		element->mle_type = MAC_LOMAC_TYPE_GRADE;
		element->mle_grade = d;

		if (p1 == p0 || *p1 != '\0')
			return (EINVAL);
	}

	return (0);
}