#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int a_type; int a_access_mask; } ;
typedef  TYPE_1__ ace_t ;

/* Variables and functions */
 int ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int ACE_ACCESS_DENIED_ACE_TYPE ; 
 int ACE_DELETE ; 
 int ACE_READ_DATA ; 
 int ACE_READ_NAMED_ATTRS ; 
 int ACE_SYNCHRONIZE ; 
 int ACE_WRITE_ATTRIBUTES ; 
 int ACE_WRITE_DATA ; 
 int ACE_WRITE_NAMED_ATTRS ; 
 int ACE_WRITE_OWNER ; 
 int ACL_DELETE_ERR_ALLOW ; 
 int ACL_DELETE_ERR_DENY ; 
 int ACL_DELETE_SET_ALLOW ; 
 int ACL_DELETE_SET_DENY ; 
 int ACL_READ_NAMED_READER_ERR_ALLOW ; 
 int ACL_READ_NAMED_READER_ERR_DENY ; 
 int ACL_READ_NAMED_READER_SET_ALLOW ; 
 int ACL_READ_NAMED_READER_SET_DENY ; 
 int ACL_SYNCHRONIZE_ERR_ALLOW ; 
 int ACL_SYNCHRONIZE_ERR_DENY ; 
 int ACL_SYNCHRONIZE_SET_ALLOW ; 
 int ACL_SYNCHRONIZE_SET_DENY ; 
 int ACL_WRITE_ATTRS_OWNER_ERR_ALLOW ; 
 int ACL_WRITE_ATTRS_OWNER_ERR_DENY ; 
 int ACL_WRITE_ATTRS_OWNER_SET_ALLOW ; 
 int ACL_WRITE_ATTRS_OWNER_SET_DENY ; 
 int ACL_WRITE_ATTRS_WRITER_ERR_ALLOW ; 
 int ACL_WRITE_ATTRS_WRITER_ERR_DENY ; 
 int ACL_WRITE_ATTRS_WRITER_SET_ALLOW ; 
 int ACL_WRITE_ATTRS_WRITER_SET_DENY ; 
 int ACL_WRITE_NAMED_WRITER_ERR_ALLOW ; 
 int ACL_WRITE_NAMED_WRITER_ERR_DENY ; 
 int ACL_WRITE_NAMED_WRITER_SET_ALLOW ; 
 int ACL_WRITE_NAMED_WRITER_SET_DENY ; 
 int ACL_WRITE_OWNER_ERR_ALLOW ; 
 int ACL_WRITE_OWNER_ERR_DENY ; 
 int ACL_WRITE_OWNER_SET_ALLOW ; 
 int ACL_WRITE_OWNER_SET_DENY ; 
 int EINVAL ; 
 int ENOTSUP ; 

__attribute__((used)) static int
access_mask_check(ace_t *acep, int mask_bit, int isowner)
{
	int set_deny, err_deny;
	int set_allow, err_allow;
	int acl_consume;
	int haswriteperm, hasreadperm;

	if (acep->a_type == ACE_ACCESS_DENIED_ACE_TYPE) {
		haswriteperm = (acep->a_access_mask & ACE_WRITE_DATA) ? 0 : 1;
		hasreadperm = (acep->a_access_mask & ACE_READ_DATA) ? 0 : 1;
	} else {
		haswriteperm = (acep->a_access_mask & ACE_WRITE_DATA) ? 1 : 0;
		hasreadperm = (acep->a_access_mask & ACE_READ_DATA) ? 1 : 0;
	}

	acl_consume = (ACL_SYNCHRONIZE_ERR_DENY |
	    ACL_DELETE_ERR_DENY |
	    ACL_WRITE_OWNER_ERR_DENY |
	    ACL_WRITE_OWNER_ERR_ALLOW |
	    ACL_WRITE_ATTRS_OWNER_SET_ALLOW |
	    ACL_WRITE_ATTRS_OWNER_ERR_DENY |
	    ACL_WRITE_ATTRS_WRITER_SET_DENY |
	    ACL_WRITE_ATTRS_WRITER_ERR_ALLOW |
	    ACL_WRITE_NAMED_WRITER_ERR_DENY |
	    ACL_READ_NAMED_READER_ERR_DENY);

	if (mask_bit == ACE_SYNCHRONIZE) {
		set_deny = ACL_SYNCHRONIZE_SET_DENY;
		err_deny =  ACL_SYNCHRONIZE_ERR_DENY;
		set_allow = ACL_SYNCHRONIZE_SET_ALLOW;
		err_allow = ACL_SYNCHRONIZE_ERR_ALLOW;
	} else if (mask_bit == ACE_WRITE_OWNER) {
		set_deny = ACL_WRITE_OWNER_SET_DENY;
		err_deny =  ACL_WRITE_OWNER_ERR_DENY;
		set_allow = ACL_WRITE_OWNER_SET_ALLOW;
		err_allow = ACL_WRITE_OWNER_ERR_ALLOW;
	} else if (mask_bit == ACE_DELETE) {
		set_deny = ACL_DELETE_SET_DENY;
		err_deny =  ACL_DELETE_ERR_DENY;
		set_allow = ACL_DELETE_SET_ALLOW;
		err_allow = ACL_DELETE_ERR_ALLOW;
	} else if (mask_bit == ACE_WRITE_ATTRIBUTES) {
		if (isowner) {
			set_deny = ACL_WRITE_ATTRS_OWNER_SET_DENY;
			err_deny =  ACL_WRITE_ATTRS_OWNER_ERR_DENY;
			set_allow = ACL_WRITE_ATTRS_OWNER_SET_ALLOW;
			err_allow = ACL_WRITE_ATTRS_OWNER_ERR_ALLOW;
		} else if (haswriteperm) {
			set_deny = ACL_WRITE_ATTRS_WRITER_SET_DENY;
			err_deny =  ACL_WRITE_ATTRS_WRITER_ERR_DENY;
			set_allow = ACL_WRITE_ATTRS_WRITER_SET_ALLOW;
			err_allow = ACL_WRITE_ATTRS_WRITER_ERR_ALLOW;
		} else {
			if ((acep->a_access_mask & mask_bit) &&
			    (acep->a_type & ACE_ACCESS_ALLOWED_ACE_TYPE)) {
				return (ENOTSUP);
			}
			return (0);
		}
	} else if (mask_bit == ACE_READ_NAMED_ATTRS) {
		if (!hasreadperm)
			return (0);

		set_deny = ACL_READ_NAMED_READER_SET_DENY;
		err_deny = ACL_READ_NAMED_READER_ERR_DENY;
		set_allow = ACL_READ_NAMED_READER_SET_ALLOW;
		err_allow = ACL_READ_NAMED_READER_ERR_ALLOW;
	} else if (mask_bit == ACE_WRITE_NAMED_ATTRS) {
		if (!haswriteperm)
			return (0);

		set_deny = ACL_WRITE_NAMED_WRITER_SET_DENY;
		err_deny = ACL_WRITE_NAMED_WRITER_ERR_DENY;
		set_allow = ACL_WRITE_NAMED_WRITER_SET_ALLOW;
		err_allow = ACL_WRITE_NAMED_WRITER_ERR_ALLOW;
	} else {
		return (EINVAL);
	}

	if (acep->a_type == ACE_ACCESS_DENIED_ACE_TYPE) {
		if (acl_consume & set_deny) {
			if (!(acep->a_access_mask & mask_bit)) {
				return (ENOTSUP);
			}
		} else if (acl_consume & err_deny) {
			if (acep->a_access_mask & mask_bit) {
				return (ENOTSUP);
			}
		}
	} else {
		/* ACE_ACCESS_ALLOWED_ACE_TYPE */
		if (acl_consume & set_allow) {
			if (!(acep->a_access_mask & mask_bit)) {
				return (ENOTSUP);
			}
		} else if (acl_consume & err_allow) {
			if (acep->a_access_mask & mask_bit) {
				return (ENOTSUP);
			}
		}
	}
	return (0);
}