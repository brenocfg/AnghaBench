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
struct mac_mls {int /*<<< orphan*/  mm_flags; int /*<<< orphan*/  mm_rangehigh; int /*<<< orphan*/  mm_rangelow; int /*<<< orphan*/  mm_effective; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAC_MLS_FLAG_EFFECTIVE ; 
 int /*<<< orphan*/  MAC_MLS_FLAG_RANGE ; 
 int /*<<< orphan*/  bzero (struct mac_mls*,int) ; 
 int mls_parse_element (int /*<<< orphan*/ *,char*) ; 
 int mls_valid (struct mac_mls*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
mls_parse(struct mac_mls *mm, char *string)
{
	char *rangehigh, *rangelow, *effective;
	int error;

	effective = strsep(&string, "(");
	if (*effective == '\0')
		effective = NULL;

	if (string != NULL) {
		rangelow = strsep(&string, "-");
		if (string == NULL)
			return (EINVAL);
		rangehigh = strsep(&string, ")");
		if (string == NULL)
			return (EINVAL);
		if (*string != '\0')
			return (EINVAL);
	} else {
		rangelow = NULL;
		rangehigh = NULL;
	}

	KASSERT((rangelow != NULL && rangehigh != NULL) ||
	    (rangelow == NULL && rangehigh == NULL),
	    ("mls_parse: range mismatch"));

	bzero(mm, sizeof(*mm));
	if (effective != NULL) {
		error = mls_parse_element(&mm->mm_effective, effective);
		if (error)
			return (error);
		mm->mm_flags |= MAC_MLS_FLAG_EFFECTIVE;
	}

	if (rangelow != NULL) {
		error = mls_parse_element(&mm->mm_rangelow, rangelow);
		if (error)
			return (error);
		error = mls_parse_element(&mm->mm_rangehigh, rangehigh);
		if (error)
			return (error);
		mm->mm_flags |= MAC_MLS_FLAG_RANGE;
	}

	error = mls_valid(mm);
	if (error)
		return (error);

	return (0);
}