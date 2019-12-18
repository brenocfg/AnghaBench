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
struct TYPE_4__ {scalar_t__ klen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ svn_sort__item_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
svn_sort_compare_items_lexically(const svn_sort__item_t *a,
                                 const svn_sort__item_t *b)
{
  int val;
  apr_size_t len;

  /* Compare bytes of a's key and b's key up to the common length. */
  len = (a->klen < b->klen) ? a->klen : b->klen;
  val = memcmp(a->key, b->key, len);
  if (val != 0)
    return val;

  /* They match up until one of them ends; whichever is longer is greater. */
  return (a->klen < b->klen) ? -1 : (a->klen > b->klen) ? 1 : 0;
}