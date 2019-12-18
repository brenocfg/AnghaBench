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
struct TYPE_4__ {scalar_t__ expanded_size; int /*<<< orphan*/  sha1_digest; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_fs_x__representation_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ svn_fs_x__id_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_fs_x__file_text_rep_equal(svn_fs_x__representation_t *a,
                              svn_fs_x__representation_t *b)
{
  svn_boolean_t a_empty = a == NULL || a->expanded_size == 0;
  svn_boolean_t b_empty = b == NULL || b->expanded_size == 0;

  /* This makes sure that neither rep will be NULL later on */
  if (a_empty && b_empty)
    return TRUE;

  if (a_empty != b_empty)
    return FALSE;

  /* Same physical representation?  Note that these IDs are always up-to-date
     instead of e.g. being set lazily. */
  if (svn_fs_x__id_eq(&a->id, &b->id))
    return TRUE;

  /* Contents are equal if the checksums match.  These are also always known.
   */
  return memcmp(a->md5_digest, b->md5_digest, sizeof(a->md5_digest)) == 0
      && memcmp(a->sha1_digest, b->sha1_digest, sizeof(a->sha1_digest)) == 0;
}