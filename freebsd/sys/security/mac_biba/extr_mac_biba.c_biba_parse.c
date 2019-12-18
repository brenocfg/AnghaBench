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
struct mac_biba {int /*<<< orphan*/  mb_flags; int /*<<< orphan*/  mb_rangehigh; int /*<<< orphan*/  mb_rangelow; int /*<<< orphan*/  mb_effective; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAC_BIBA_FLAG_EFFECTIVE ; 
 int /*<<< orphan*/  MAC_BIBA_FLAG_RANGE ; 
 int biba_parse_element (int /*<<< orphan*/ *,char*) ; 
 int biba_valid (struct mac_biba*) ; 
 int /*<<< orphan*/  bzero (struct mac_biba*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
biba_parse(struct mac_biba *mb, char *string)
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
	    ("biba_parse: range mismatch"));

	bzero(mb, sizeof(*mb));
	if (effective != NULL) {
		error = biba_parse_element(&mb->mb_effective, effective);
		if (error)
			return (error);
		mb->mb_flags |= MAC_BIBA_FLAG_EFFECTIVE;
	}

	if (rangelow != NULL) {
		error = biba_parse_element(&mb->mb_rangelow, rangelow);
		if (error)
			return (error);
		error = biba_parse_element(&mb->mb_rangehigh, rangehigh);
		if (error)
			return (error);
		mb->mb_flags |= MAC_BIBA_FLAG_RANGE;
	}

	error = biba_valid(mb);
	if (error)
		return (error);

	return (0);
}