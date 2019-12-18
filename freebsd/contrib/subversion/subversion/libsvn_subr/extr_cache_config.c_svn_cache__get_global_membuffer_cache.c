#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  initialize_cache ; 
 int /*<<< orphan*/ * svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

svn_membuffer_t *
svn_cache__get_global_membuffer_cache(void)
{
  static svn_membuffer_t *cache = NULL;
  static svn_atomic_t initialized = 0;

  svn_error_t *err
    = svn_atomic__init_once(&initialized, initialize_cache, &cache, NULL);
  if (err)
    {
      /* no caches today ... */
      svn_error_clear(err);
      return NULL;
    }

  return cache;
}