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
typedef  int uint32_t ;
typedef  int mode_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ACE_APPEND_DATA ; 
 int ACE_DELETE_CHILD ; 
 int ACE_EXECUTE ; 
 int ACE_READ_ACL ; 
 int ACE_READ_ATTRIBUTES ; 
 int ACE_READ_DATA ; 
 int ACE_WRITE_ACL ; 
 int ACE_WRITE_DATA ; 
 int S_IROTH ; 
 int S_IWOTH ; 
 int S_IXOTH ; 
 int access_mask_set (int,int,int,int) ; 

__attribute__((used)) static uint32_t
mode_to_ace_access(mode_t mode, boolean_t isdir, int isowner, int isallow)
{
	uint32_t access = 0;
	int haswriteperm = 0;
	int hasreadperm = 0;

	if (isallow) {
		haswriteperm = (mode & S_IWOTH);
		hasreadperm = (mode & S_IROTH);
	} else {
		haswriteperm = !(mode & S_IWOTH);
		hasreadperm = !(mode & S_IROTH);
	}

	/*
	 * The following call takes care of correctly setting the following
	 * mask bits in the access_mask:
	 * ACE_SYNCHRONIZE, ACE_WRITE_OWNER, ACE_DELETE,
	 * ACE_WRITE_ATTRIBUTES, ACE_WRITE_NAMED_ATTRS, ACE_READ_NAMED_ATTRS
	 */
	access = access_mask_set(haswriteperm, hasreadperm, isowner, isallow);

	if (isallow) {
		access |= ACE_READ_ACL | ACE_READ_ATTRIBUTES;
		if (isowner)
			access |= ACE_WRITE_ACL;
	} else {
		if (! isowner)
			access |= ACE_WRITE_ACL;
	}

	/* read */
	if (mode & S_IROTH) {
		access |= ACE_READ_DATA;
	}
	/* write */
	if (mode & S_IWOTH) {
		access |= ACE_WRITE_DATA |
		    ACE_APPEND_DATA;
		if (isdir)
			access |= ACE_DELETE_CHILD;
	}
	/* exec */
	if (mode & S_IXOTH) {
		access |= ACE_EXECUTE;
	}

	return (access);
}