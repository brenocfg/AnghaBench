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
struct mac_lomac {int /*<<< orphan*/  ml_flags; int /*<<< orphan*/  ml_rangehigh; int /*<<< orphan*/  ml_rangelow; int /*<<< orphan*/  ml_auxsingle; int /*<<< orphan*/  ml_single; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAC_LOMAC_FLAG_AUX ; 
 int /*<<< orphan*/  MAC_LOMAC_FLAG_RANGE ; 
 int /*<<< orphan*/  MAC_LOMAC_FLAG_SINGLE ; 
 int /*<<< orphan*/  bzero (struct mac_lomac*,int) ; 
 int lomac_parse_element (int /*<<< orphan*/ *,char*) ; 
 int lomac_valid (struct mac_lomac*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
lomac_parse(struct mac_lomac *ml, char *string)
{
	char *range, *rangeend, *rangehigh, *rangelow, *single, *auxsingle,
	    *auxsingleend;
	int error;

	/* Do we have a range? */
	single = string;
	range = strchr(string, '(');
	if (range == single)
		single = NULL;
	auxsingle = strchr(string, '[');
	if (auxsingle == single)
		single = NULL;
	if (range != NULL && auxsingle != NULL)
		return (EINVAL);
	rangelow = rangehigh = NULL;
	if (range != NULL) {
		/* Nul terminate the end of the single string. */
		*range = '\0';
		range++;
		rangelow = range;
		rangehigh = strchr(rangelow, '-');
		if (rangehigh == NULL)
			return (EINVAL);
		rangehigh++;
		if (*rangelow == '\0' || *rangehigh == '\0')
			return (EINVAL);
		rangeend = strchr(rangehigh, ')');
		if (rangeend == NULL)
			return (EINVAL);
		if (*(rangeend + 1) != '\0')
			return (EINVAL);
		/* Nul terminate the ends of the ranges. */
		*(rangehigh - 1) = '\0';
		*rangeend = '\0';
	}
	KASSERT((rangelow != NULL && rangehigh != NULL) ||
	    (rangelow == NULL && rangehigh == NULL),
	    ("lomac_internalize_label: range mismatch"));
	if (auxsingle != NULL) {
		/* Nul terminate the end of the single string. */
		*auxsingle = '\0';
		auxsingle++;
		auxsingleend = strchr(auxsingle, ']');
		if (auxsingleend == NULL)
			return (EINVAL);
		if (*(auxsingleend + 1) != '\0')
			return (EINVAL);
		/* Nul terminate the end of the auxsingle. */
		*auxsingleend = '\0';
	}

	bzero(ml, sizeof(*ml));
	if (single != NULL) {
		error = lomac_parse_element(&ml->ml_single, single);
		if (error)
			return (error);
		ml->ml_flags |= MAC_LOMAC_FLAG_SINGLE;
	}

	if (auxsingle != NULL) {
		error = lomac_parse_element(&ml->ml_auxsingle, auxsingle);
		if (error)
			return (error);
		ml->ml_flags |= MAC_LOMAC_FLAG_AUX;
	}

	if (rangelow != NULL) {
		error = lomac_parse_element(&ml->ml_rangelow, rangelow);
		if (error)
			return (error);
		error = lomac_parse_element(&ml->ml_rangehigh, rangehigh);
		if (error)
			return (error);
		ml->ml_flags |= MAC_LOMAC_FLAG_RANGE;
	}

	error = lomac_valid(ml);
	if (error)
		return (error);

	return (0);
}