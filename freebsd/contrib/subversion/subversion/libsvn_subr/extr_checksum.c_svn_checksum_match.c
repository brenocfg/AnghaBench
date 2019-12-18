#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int kind; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * digest_sizes ; 
 int /*<<< orphan*/  svn__digests_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 

svn_boolean_t
svn_checksum_match(const svn_checksum_t *checksum1,
                   const svn_checksum_t *checksum2)
{
  if (checksum1 == NULL || checksum2 == NULL)
    return TRUE;

  if (checksum1->kind != checksum2->kind)
    return FALSE;

  switch (checksum1->kind)
    {
      case svn_checksum_md5:
      case svn_checksum_sha1:
      case svn_checksum_fnv1a_32:
      case svn_checksum_fnv1a_32x4:
        return svn__digests_match(checksum1->digest,
                                  checksum2->digest,
                                  digest_sizes[checksum1->kind]);

      default:
        /* We really shouldn't get here, but if we do... */
        return FALSE;
    }
}