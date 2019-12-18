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
struct TYPE_3__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const char *
hash_fetch(apr_hash_t *hash,
           const char *key)
{
  svn_string_t *str = svn_hash_gets(hash, key);
  return str ? str->data : NULL;
}