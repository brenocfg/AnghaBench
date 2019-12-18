#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uid_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_9__ {int a_type; int a_perm; void* a_id; } ;
typedef  TYPE_1__ aclent_t ;
struct TYPE_10__ {int a_flags; void* a_who; void* a_access_mask; int /*<<< orphan*/  a_type; } ;
typedef  TYPE_2__ ace_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ACCESS_DENIED_ACE_TYPE ; 
 int ACE_DIRECTORY_INHERIT_ACE ; 
 int ACE_EVERYONE ; 
 int ACE_FILE_INHERIT_ACE ; 
 int ACE_GROUP ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_INHERIT_ONLY_ACE ; 
 int ACE_OWNER ; 
 int ACL_DEFAULT ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int CLASS_OBJ ; 
 int EINVAL ; 
 int GROUP ; 
 int GROUP_OBJ ; 
 int OTHER_OBJ ; 
 int USER ; 
 int USER_OBJ ; 
 int /*<<< orphan*/  ace_make_deny (TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cacl_free (TYPE_2__*,int) ; 
 scalar_t__ cacl_malloc (void**,int) ; 
 int /*<<< orphan*/  cmp2acls ; 
 int /*<<< orphan*/  ksort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int ln_aent_preprocess (TYPE_1__*,int,int*,int*,int*,int*,int*) ; 
 void* mode_to_ace_access (int,int,int,int) ; 

__attribute__((used)) static int
ln_aent_to_ace(aclent_t *aclent, int n, ace_t **acepp, int *rescount, int isdir)
{
	int error = 0;
	mode_t mask;
	int numuser, numgroup, needsort;
	int resultsize = 0;
	int i, groupi = 0, skip;
	ace_t *acep, *result = NULL;
	int hasmask;

	error = ln_aent_preprocess(aclent, n, &hasmask, &mask,
	    &numuser, &numgroup, &needsort);
	if (error != 0)
		goto out;

	/* allow + deny for each aclent */
	resultsize = n * 2;
	if (hasmask) {
		/*
		 * stick extra deny on the group_obj and on each
		 * user|group for the mask (the group_obj was added
		 * into the count for numgroup)
		 */
		resultsize += numuser + numgroup;
		/* ... and don't count the mask itself */
		resultsize -= 2;
	}

	/* sort the source if necessary */
	if (needsort)
		ksort((caddr_t)aclent, n, sizeof (aclent_t), cmp2acls);

	if (cacl_malloc((void **)&result, resultsize * sizeof (ace_t)) != 0)
		goto out;

	acep = result;

	for (i = 0; i < n; i++) {
		/*
		 * don't process CLASS_OBJ (mask); mask was grabbed in
		 * ln_aent_preprocess()
		 */
		if (aclent[i].a_type & CLASS_OBJ)
			continue;

		/* If we need an ACL_MASK emulator, prepend it now */
		if ((hasmask) &&
		    (aclent[i].a_type & (USER | GROUP | GROUP_OBJ))) {
			acep->a_type = ACE_ACCESS_DENIED_ACE_TYPE;
			acep->a_flags = 0;
			if (aclent[i].a_type & GROUP_OBJ) {
				acep->a_who = (uid_t)-1;
				acep->a_flags |=
				    (ACE_IDENTIFIER_GROUP|ACE_GROUP);
			} else if (aclent[i].a_type & USER) {
				acep->a_who = aclent[i].a_id;
			} else {
				acep->a_who = aclent[i].a_id;
				acep->a_flags |= ACE_IDENTIFIER_GROUP;
			}
			if (aclent[i].a_type & ACL_DEFAULT) {
				acep->a_flags |= ACE_INHERIT_ONLY_ACE |
				    ACE_FILE_INHERIT_ACE |
				    ACE_DIRECTORY_INHERIT_ACE;
			}
			/*
			 * Set the access mask for the prepended deny
			 * ace.  To do this, we invert the mask (found
			 * in ln_aent_preprocess()) then convert it to an
			 * DENY ace access_mask.
			 */
			acep->a_access_mask = mode_to_ace_access((mask ^ 07),
			    isdir, 0, 0);
			acep += 1;
		}

		/* handle a_perm -> access_mask */
		acep->a_access_mask = mode_to_ace_access(aclent[i].a_perm,
		    isdir, aclent[i].a_type & USER_OBJ, 1);

		/* emulate a default aclent */
		if (aclent[i].a_type & ACL_DEFAULT) {
			acep->a_flags |= ACE_INHERIT_ONLY_ACE |
			    ACE_FILE_INHERIT_ACE |
			    ACE_DIRECTORY_INHERIT_ACE;
		}

		/*
		 * handle a_perm and a_id
		 *
		 * this must be done last, since it involves the
		 * corresponding deny aces, which are handled
		 * differently for each different a_type.
		 */
		if (aclent[i].a_type & USER_OBJ) {
			acep->a_who = (uid_t)-1;
			acep->a_flags |= ACE_OWNER;
			ace_make_deny(acep, acep + 1, isdir, B_TRUE);
			acep += 2;
		} else if (aclent[i].a_type & USER) {
			acep->a_who = aclent[i].a_id;
			ace_make_deny(acep, acep + 1, isdir, B_FALSE);
			acep += 2;
		} else if (aclent[i].a_type & (GROUP_OBJ | GROUP)) {
			if (aclent[i].a_type & GROUP_OBJ) {
				acep->a_who = (uid_t)-1;
				acep->a_flags |= ACE_GROUP;
			} else {
				acep->a_who = aclent[i].a_id;
			}
			acep->a_flags |= ACE_IDENTIFIER_GROUP;
			/*
			 * Set the corresponding deny for the group ace.
			 *
			 * The deny aces go after all of the groups, unlike
			 * everything else, where they immediately follow
			 * the allow ace.
			 *
			 * We calculate "skip", the number of slots to
			 * skip ahead for the deny ace, here.
			 *
			 * The pattern is:
			 * MD1 A1 MD2 A2 MD3 A3 D1 D2 D3
			 * thus, skip is
			 * (2 * numgroup) - 1 - groupi
			 * (2 * numgroup) to account for MD + A
			 * - 1 to account for the fact that we're on the
			 * access (A), not the mask (MD)
			 * - groupi to account for the fact that we have
			 * passed up groupi number of MD's.
			 */
			skip = (2 * numgroup) - 1 - groupi;
			ace_make_deny(acep, acep + skip, isdir, B_FALSE);
			/*
			 * If we just did the last group, skip acep past
			 * all of the denies; else, just move ahead one.
			 */
			if (++groupi >= numgroup)
				acep += numgroup + 1;
			else
				acep += 1;
		} else if (aclent[i].a_type & OTHER_OBJ) {
			acep->a_who = (uid_t)-1;
			acep->a_flags |= ACE_EVERYONE;
			ace_make_deny(acep, acep + 1, isdir, B_FALSE);
			acep += 2;
		} else {
			error = EINVAL;
			goto out;
		}
	}

	*acepp = result;
	*rescount = resultsize;

out:
	if (error != 0) {
		if ((result != NULL) && (resultsize > 0)) {
			cacl_free(result, resultsize * sizeof (ace_t));
		}
	}

	return (error);
}