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
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void const*) ; 

void
svn_hash__sets_debug(apr_hash_t *ht, const char *key, const void *val)
{
  apr_hash_set(ht, key, APR_HASH_KEY_STRING, val);
}