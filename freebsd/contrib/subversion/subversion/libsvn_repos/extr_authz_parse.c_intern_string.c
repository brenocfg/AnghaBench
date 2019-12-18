#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  strings; TYPE_1__* authz; } ;
typedef  TYPE_2__ ctor_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 char* apr_hash_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static const char *
intern_string(ctor_baton_t *cb, const char *str, apr_size_t len)
{
  const char *interned;

  if (len == (apr_size_t)-1)
    len = strlen(str);

  interned = apr_hash_get(cb->strings, str, len);
  if (!interned)
    {
      interned = apr_pstrmemdup(cb->authz->pool, str, len);
      apr_hash_set(cb->strings, interned, len, interned);
    }
  return interned;
}