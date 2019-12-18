#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct udf_node {TYPE_2__* fentry; } ;
typedef  int mode_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ icbtag; int /*<<< orphan*/  perm; } ;

/* Variables and functions */
 int UDF_FENTRY_PERM_GRP_MASK ; 
 int UDF_FENTRY_PERM_OWNER_MASK ; 
 int UDF_FENTRY_PERM_USER_MASK ; 
 int UDF_ICB_TAG_FLAGS_SETGID ; 
 int UDF_ICB_TAG_FLAGS_SETUID ; 
 int UDF_ICB_TAG_FLAGS_STICKY ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mode_t
udf_permtomode(struct udf_node *node)
{
	uint32_t perm;
	uint16_t flags;
	mode_t mode;

	perm = le32toh(node->fentry->perm);
	flags = le16toh(node->fentry->icbtag.flags);

	mode = perm & UDF_FENTRY_PERM_USER_MASK;
	mode |= ((perm & UDF_FENTRY_PERM_GRP_MASK) >> 2);
	mode |= ((perm & UDF_FENTRY_PERM_OWNER_MASK) >> 4);
	mode |= ((flags & UDF_ICB_TAG_FLAGS_STICKY) << 4);
	mode |= ((flags & UDF_ICB_TAG_FLAGS_SETGID) << 6);
	mode |= ((flags & UDF_ICB_TAG_FLAGS_SETUID) << 8);

	return (mode);
}