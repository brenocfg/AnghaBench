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
struct TYPE_2__ {long long ivalue; char* svalue; } ;
struct editentry {int type; TYPE_1__ value; int /*<<< orphan*/  size; int /*<<< orphan*/  editable; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  EX_OSERR ; 
 long long RESOLUTION_MAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 
 struct editentry* editentry_lookup (char*) ; 
 int editlist_changed ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  returnerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 long long strtoll (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,long long,char*,long long) ; 

__attribute__((used)) static int
editentry_set(char *name, char *newvalue, int editonly)
{
	struct editentry *dest;	/* Modepage entry to update. */
	char *cval;		/* Pointer to new string value. */
	char *convertend;	/* End-of-conversion pointer. */
	long long ival, newival; /* New integral value. */
	int resolution;		/* Resolution in bits for integer conversion. */

/*
 * Macro to determine the maximum value of the given size for the current
 * resolution.
 */
#define	RESOLUTION_MAX(size)	((1LL << (resolution * (size))) - 1)

	assert(newvalue != NULL);
	if (*newvalue == '\0')
		return (0);	/* Nothing to do. */

	if ((dest = editentry_lookup(name)) == NULL)
		returnerr(ENOENT);
	if (!dest->editable && editonly)
		returnerr(EPERM);

	switch (dest->type) {
	case 'i':		/* Byte-sized integral type. */
	case 'b':		/* Bit-sized integral types. */
	case 't':
		/* Convert the value string to an integer. */
		resolution = (dest->type == 'i')? 8: 1;
		ival = strtoll(newvalue, &convertend, 0);
		if (*convertend != '\0')
			returnerr(EINVAL);
		if (ival > RESOLUTION_MAX(dest->size) || ival < 0) {
			newival = (ival < 0) ? 0 : RESOLUTION_MAX(dest->size);
			warnx("value %lld is out of range for entry %s; "
			    "clipping to %lld", ival, name, newival);
			ival = newival;
		}
		if (dest->value.ivalue != ival)
			editlist_changed = 1;
		dest->value.ivalue = ival;
		break;

	case 'c':		/* Character array. */
	case 'z':		/* Null-padded string. */
		if ((cval = malloc(dest->size + 1)) == NULL)
			err(EX_OSERR, NULL);
		bzero(cval, dest->size + 1);
		strncpy(cval, newvalue, dest->size);
		if (dest->type == 'z') {
			/* Convert trailing spaces to nulls. */
			char *convertend2;

			for (convertend2 = cval + dest->size;
			    convertend2 >= cval; convertend2--) {
				if (*convertend2 == ' ')
					*convertend2 = '\0';
				else if (*convertend2 != '\0')
					break;
			}
		}
		if (strncmp(dest->value.svalue, cval, dest->size) == 0) {
			/* Nothing changed, free the newly allocated string. */
			free(cval);
			break;
		}
		if (dest->value.svalue != NULL) {
			/* Free the current string buffer. */
			free(dest->value.svalue);
			dest->value.svalue = NULL;
		}
		dest->value.svalue = cval;
		editlist_changed = 1;
		break;

	default:
		; /* NOTREACHED */
	}

	return (0);
#undef RESOLUTION_MAX
}