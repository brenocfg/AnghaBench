#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int a_access_mask; int /*<<< orphan*/  a_type; int /*<<< orphan*/  a_who; } ;
typedef  TYPE_1__ ace_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ACCESS_DENIED_ACE_TYPE ; 
 int ACE_DELETE ; 
 int ACE_DELETE_CHILD ; 
 int ACE_POSIX_SUPPORTED_BITS ; 
 int ACE_READ_DATA ; 
 int ACE_READ_NAMED_ATTRS ; 
 int ACE_SYNCHRONIZE ; 
 int ACE_WRITE_ATTRIBUTES ; 
 int ACE_WRITE_DATA ; 
 int ACE_WRITE_NAMED_ATTRS ; 
 int ACE_WRITE_OWNER ; 
 int /*<<< orphan*/  B_FALSE ; 
 int access_mask_set (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
ace_make_deny(ace_t *allow, ace_t *deny, int isdir, int isowner)
{
	(void) memcpy(deny, allow, sizeof (ace_t));

	deny->a_who = allow->a_who;

	deny->a_type = ACE_ACCESS_DENIED_ACE_TYPE;
	deny->a_access_mask ^= ACE_POSIX_SUPPORTED_BITS;
	if (isdir)
		deny->a_access_mask ^= ACE_DELETE_CHILD;

	deny->a_access_mask &= ~(ACE_SYNCHRONIZE | ACE_WRITE_OWNER |
	    ACE_DELETE | ACE_WRITE_ATTRIBUTES | ACE_READ_NAMED_ATTRS |
	    ACE_WRITE_NAMED_ATTRS);
	deny->a_access_mask |= access_mask_set((allow->a_access_mask &
	    ACE_WRITE_DATA), (allow->a_access_mask & ACE_READ_DATA), isowner,
	    B_FALSE);
}