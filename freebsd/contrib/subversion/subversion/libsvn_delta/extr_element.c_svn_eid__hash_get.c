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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 void* apr_hash_get (int /*<<< orphan*/ *,int*,int) ; 

void *
svn_eid__hash_get(apr_hash_t *ht,
                  int key)
{
  return apr_hash_get(ht, &key, sizeof(key));
}