#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* next; struct TYPE_15__* children; scalar_t__ is_atom; } ;
typedef  TYPE_6__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_14__ {char* data; scalar_t__ is_atom; TYPE_4__* next; } ;
struct TYPE_13__ {int /*<<< orphan*/  is_atom; TYPE_3__* next; } ;
struct TYPE_12__ {int /*<<< orphan*/  is_atom; TYPE_2__* next; } ;
struct TYPE_11__ {TYPE_1__* next; scalar_t__ is_atom; } ;
struct TYPE_10__ {scalar_t__ is_atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int svn_skel__list_length (TYPE_6__*) ; 

__attribute__((used)) static svn_boolean_t
is_valid_node_revision_header_skel(svn_skel_t *skel, svn_skel_t **kind_p)
{
  int len = svn_skel__list_length(skel);

  if (len < 2)
    return FALSE;

  /* set the *KIND_P pointer. */
  *kind_p = skel->children;

  /* check for valid lengths. */
  if (! ((len == 2) || (len == 3) || (len == 4) || (len == 6)))
    return FALSE;

  /* got mergeinfo stuff? */
  if ((len > 4)
      && (! (skel->children->next->next->next->next->is_atom
             && skel->children->next->next->next->next->next->is_atom)))
    return FALSE;

  /* got predecessor count? */
  if ((len > 3)
      && (! skel->children->next->next->next->is_atom))
    return FALSE;

  /* got predecessor? */
  if ((len > 2)
      && (! skel->children->next->next->is_atom))
    return FALSE;

  /* got the basics? */
  if (! (skel->children->is_atom
         && skel->children->next->is_atom
         && (skel->children->next->data[0] == '/')))
    return FALSE;

  return TRUE;
}