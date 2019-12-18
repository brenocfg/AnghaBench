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
struct TYPE_4__ {char const* data; int len; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int getsize (char const*,int,char const**,int) ; 
 scalar_t__* skel_char_type ; 
 scalar_t__ type_space ; 

__attribute__((used)) static svn_skel_t *
explicit_atom(const char *data,
              apr_size_t len,
              apr_pool_t *pool)
{
  const char *end = data + len;
  const char *next;
  apr_size_t size;
  svn_skel_t *s;

  /* Parse the length.  */
  size = getsize(data, end - data, &next, end - data);
  data = next;

  /* Exit if we overflowed, or there wasn't a valid number there.  */
  if (! data)
    return NULL;

  /* Skip the whitespace character after the length.  */
  if (data >= end || skel_char_type[(unsigned char) *data] != type_space)
    return NULL;
  data++;

  /* Check the length.  */
  if (end - data < size)
    return NULL;

  /* Allocate the skel representing this string.  */
  s = apr_pcalloc(pool, sizeof(*s));
  s->is_atom = TRUE;
  s->data = data;
  s->len = size;

  return s;
}