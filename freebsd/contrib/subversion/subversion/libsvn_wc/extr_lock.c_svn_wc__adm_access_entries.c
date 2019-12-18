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
struct TYPE_3__ {int /*<<< orphan*/ * entries_all; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */

apr_hash_t *
svn_wc__adm_access_entries(svn_wc_adm_access_t *adm_access)
{
  /* Compile with -DSVN_DISABLE_ENTRY_CACHE to disable the in-memory
     entry caching. As of 2010-03-18 (r924708) merge_tests 34 and 134
     fail during "make check".  */
#ifdef SVN_DISABLE_ENTRY_CACHE
  return NULL;
#else
  return adm_access->entries_all;
#endif
}