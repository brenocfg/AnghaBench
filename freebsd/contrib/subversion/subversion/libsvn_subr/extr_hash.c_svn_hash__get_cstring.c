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
 char* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

const char *
svn_hash__get_cstring(apr_hash_t *hash,
                      const char *key,
                      const char *default_value)
{
  if (hash)
    {
      const char *value = svn_hash_gets(hash, key);
      return value ? value : default_value;
    }

  return default_value;
}