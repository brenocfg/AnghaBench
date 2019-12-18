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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_DELETE ; 
 int /*<<< orphan*/  ACE_READ_NAMED_ATTRS ; 
 int /*<<< orphan*/  ACE_SYNCHRONIZE ; 
 int /*<<< orphan*/  ACE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  ACE_WRITE_NAMED_ATTRS ; 
 int /*<<< orphan*/  ACE_WRITE_OWNER ; 
 int ACL_DELETE_SET_ALLOW ; 
 int ACL_DELETE_SET_DENY ; 
 int ACL_READ_NAMED_READER_SET_ALLOW ; 
 int ACL_READ_NAMED_READER_SET_DENY ; 
 int ACL_SYNCHRONIZE_SET_ALLOW ; 
 int ACL_SYNCHRONIZE_SET_DENY ; 
 int ACL_WRITE_ATTRS_OWNER_SET_ALLOW ; 
 int ACL_WRITE_ATTRS_OWNER_SET_DENY ; 
 int ACL_WRITE_ATTRS_WRITER_SET_ALLOW ; 
 int ACL_WRITE_ATTRS_WRITER_SET_DENY ; 
 int ACL_WRITE_NAMED_WRITER_SET_ALLOW ; 
 int ACL_WRITE_NAMED_WRITER_SET_DENY ; 
 int ACL_WRITE_OWNER_SET_ALLOW ; 
 int ACL_WRITE_OWNER_SET_DENY ; 

__attribute__((used)) static uint32_t
access_mask_set(int haswriteperm, int hasreadperm, int isowner, int isallow)
{
	uint32_t access_mask = 0;
	int acl_produce;
	int synchronize_set = 0, write_owner_set = 0;
	int delete_set = 0, write_attrs_set = 0;
	int read_named_set = 0, write_named_set = 0;

	acl_produce = (ACL_SYNCHRONIZE_SET_ALLOW |
	    ACL_WRITE_ATTRS_OWNER_SET_ALLOW |
	    ACL_WRITE_ATTRS_WRITER_SET_DENY);

	if (isallow) {
		synchronize_set = ACL_SYNCHRONIZE_SET_ALLOW;
		write_owner_set = ACL_WRITE_OWNER_SET_ALLOW;
		delete_set = ACL_DELETE_SET_ALLOW;
		if (hasreadperm)
			read_named_set = ACL_READ_NAMED_READER_SET_ALLOW;
		if (haswriteperm)
			write_named_set = ACL_WRITE_NAMED_WRITER_SET_ALLOW;
		if (isowner)
			write_attrs_set = ACL_WRITE_ATTRS_OWNER_SET_ALLOW;
		else if (haswriteperm)
			write_attrs_set = ACL_WRITE_ATTRS_WRITER_SET_ALLOW;
	} else {

		synchronize_set = ACL_SYNCHRONIZE_SET_DENY;
		write_owner_set = ACL_WRITE_OWNER_SET_DENY;
		delete_set = ACL_DELETE_SET_DENY;
		if (hasreadperm)
			read_named_set = ACL_READ_NAMED_READER_SET_DENY;
		if (haswriteperm)
			write_named_set = ACL_WRITE_NAMED_WRITER_SET_DENY;
		if (isowner)
			write_attrs_set = ACL_WRITE_ATTRS_OWNER_SET_DENY;
		else if (haswriteperm)
			write_attrs_set = ACL_WRITE_ATTRS_WRITER_SET_DENY;
		else
			/*
			 * If the entity is not the owner and does not
			 * have write permissions ACE_WRITE_ATTRIBUTES will
			 * always go in the DENY ACE.
			 */
			access_mask |= ACE_WRITE_ATTRIBUTES;
	}

	if (acl_produce & synchronize_set)
		access_mask |= ACE_SYNCHRONIZE;
	if (acl_produce & write_owner_set)
		access_mask |= ACE_WRITE_OWNER;
	if (acl_produce & delete_set)
		access_mask |= ACE_DELETE;
	if (acl_produce & write_attrs_set)
		access_mask |= ACE_WRITE_ATTRIBUTES;
	if (acl_produce & read_named_set)
		access_mask |= ACE_READ_NAMED_ATTRS;
	if (acl_produce & write_named_set)
		access_mask |= ACE_WRITE_NAMED_ATTRS;

	return (access_mask);
}