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
struct TYPE_4__ {char* key; size_t klen; } ;
typedef  TYPE_1__ svn_sort__item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int svn_path_compare_paths (char const*,char const*) ; 

int
svn_sort_compare_items_as_paths(const svn_sort__item_t *a,
                                const svn_sort__item_t *b)
{
  const char *astr, *bstr;

  astr = a->key;
  bstr = b->key;
  assert(astr[a->klen] == '\0');
  assert(bstr[b->klen] == '\0');
  return svn_path_compare_paths(astr, bstr);
}