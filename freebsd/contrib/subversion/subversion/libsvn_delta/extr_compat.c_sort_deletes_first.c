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
struct TYPE_4__ {char* key; struct change_node* value; } ;
typedef  TYPE_1__ svn_sort__item_t ;
struct change_node {scalar_t__ action; } ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 scalar_t__ RESTRUCTURE_DELETE ; 
 int count_components (char const*) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int svn_path_compare_paths (char const*,char const*) ; 

__attribute__((used)) static int
sort_deletes_first(const svn_sort__item_t *item1,
                   const svn_sort__item_t *item2)
{
  const char *relpath1 = item1->key;
  const char *relpath2 = item2->key;
  const struct change_node *change1 = item1->value;
  const struct change_node *change2 = item2->value;
  const char *slash1;
  const char *slash2;
  ptrdiff_t len1;
  ptrdiff_t len2;

  /* Force the root to always sort first. Otherwise, it may look like a
     sibling of its children (no slashes), and could get sorted *after*
     any children that get deleted.  */
  if (*relpath1 == '\0')
    return -1;
  if (*relpath2 == '\0')
    return 1;

  /* Are these two items siblings? The 'if' statement tests if they are
     siblings in the root directory, or that slashes were found in both
     paths, that the length of the paths to those slashes match, and that
     the path contents up to those slashes also match.  */
  slash1 = strrchr(relpath1, '/');
  slash2 = strrchr(relpath2, '/');
  if ((slash1 == NULL && slash2 == NULL)
      || (slash1 != NULL
          && slash2 != NULL
          && (len1 = slash1 - relpath1) == (len2 = slash2 - relpath2)
          && memcmp(relpath1, relpath2, len1) == 0))
    {
      if (change1->action == RESTRUCTURE_DELETE)
        {
          if (change2->action == RESTRUCTURE_DELETE)
            {
              /* If both items are being deleted, then we don't care about
                 the order. State they are equal.  */
              return 0;
            }

          /* ITEM1 is being deleted. Sort it before the surviving item.  */
          return -1;
        }
      if (change2->action == RESTRUCTURE_DELETE)
        /* ITEM2 is being deleted. Sort it before the surviving item.  */
        return 1;

      /* Normally, we don't care about the ordering of two siblings. However,
         if these siblings are directories, then we need to provide an
         ordering so that the quicksort algorithm will further sort them
         relative to the maybe-directory's children.

         Without this additional ordering, we could see that A/B/E and A/B/F
         are equal. And then A/B/E/child is sorted before A/B/F. But since
         E and F are "equal", A/B/E could arrive *after* A/B/F and after the
         A/B/E/child node.  */

      /* FALLTHROUGH */
    }

  /* Paths-to-be-deleted with fewer components always sort earlier.

     For example, gamma will sort before E/alpha.

     Without this test, E/alpha lexicographically sorts before gamma,
     but gamma sorts before E when gamma is to be deleted. This kind of
     ordering would place E/alpha before E. Not good.

     With this test, gamma sorts before E/alpha. E and E/alpha are then
     sorted by svn_path_compare_paths() (which places E before E/alpha).  */
  if (change1->action == RESTRUCTURE_DELETE
      || change2->action == RESTRUCTURE_DELETE)
    {
      int count1 = count_components(relpath1);
      int count2 = count_components(relpath2);

      if (count1 < count2 && change1->action == RESTRUCTURE_DELETE)
        return -1;
      if (count1 > count2 && change2->action == RESTRUCTURE_DELETE)
        return 1;
    }

  /* Use svn_path_compare_paths() to get correct depth-based ordering.  */
  return svn_path_compare_paths(relpath1, relpath2);
}