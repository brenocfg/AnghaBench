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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 void* apr_hash_get (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ apr_tolower (char const) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,size_t) ; 

__attribute__((used)) static void *
get_hash_value(apr_hash_t *hash,
               svn_stringbuf_t *buffer,
               const char *key,
               svn_boolean_t case_sensitive)
{
  apr_size_t i;
  apr_size_t len = strlen(key);

  if (case_sensitive)
    return apr_hash_get(hash, key, len);

  svn_stringbuf_ensure(buffer, len);
  for (i = 0; i < len; ++i)
    buffer->data[i] = (char)apr_tolower(key[i]);

  return apr_hash_get(hash, buffer->data, len);
}