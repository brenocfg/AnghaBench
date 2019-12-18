#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* url; TYPE_3__* author; TYPE_2__* date; TYPE_1__* revision; } ;
typedef  TYPE_5__ svn_subst_keywords_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_subst_keywords_differ(const svn_subst_keywords_t *a,
                          const svn_subst_keywords_t *b,
                          svn_boolean_t compare_values)
{
  if (((a == NULL) && (b == NULL)) /* no A or B */
      /* no A, and B has no contents */
      || ((a == NULL)
          && (b->revision == NULL)
          && (b->date == NULL)
          && (b->author == NULL)
          && (b->url == NULL))
      /* no B, and A has no contents */
      || ((b == NULL)           && (a->revision == NULL)
          && (a->date == NULL)
          && (a->author == NULL)
          && (a->url == NULL))
      /* neither A nor B has any contents */
      || ((a != NULL) && (b != NULL)
          && (b->revision == NULL)
          && (b->date == NULL)
          && (b->author == NULL)
          && (b->url == NULL)
          && (a->revision == NULL)
          && (a->date == NULL)
          && (a->author == NULL)
          && (a->url == NULL)))
    {
      return FALSE;
    }
  else if ((a == NULL) || (b == NULL))
    return TRUE;

  /* Else both A and B have some keywords. */

  if ((! a->revision) != (! b->revision))
    return TRUE;
  else if ((compare_values && (a->revision != NULL))
           && (strcmp(a->revision->data, b->revision->data) != 0))
    return TRUE;

  if ((! a->date) != (! b->date))
    return TRUE;
  else if ((compare_values && (a->date != NULL))
           && (strcmp(a->date->data, b->date->data) != 0))
    return TRUE;

  if ((! a->author) != (! b->author))
    return TRUE;
  else if ((compare_values && (a->author != NULL))
           && (strcmp(a->author->data, b->author->data) != 0))
    return TRUE;

  if ((! a->url) != (! b->url))
    return TRUE;
  else if ((compare_values && (a->url != NULL))
           && (strcmp(a->url->data, b->url->data) != 0))
    return TRUE;

  /* Else we never found a difference, so they must be the same. */

  return FALSE;
}