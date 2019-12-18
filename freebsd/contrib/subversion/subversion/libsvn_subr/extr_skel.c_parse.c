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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * explicit_atom (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * implicit_atom (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__* skel_char_type ; 
 scalar_t__ type_name ; 

__attribute__((used)) static svn_skel_t *
parse(const char *data,
      apr_size_t len,
      apr_pool_t *pool)
{
  char c;

  /* The empty string isn't a valid skel.  */
  if (len <= 0)
    return NULL;

  c = *data;

  /* Is it a list, or an atom?  */
  if (c == '(')
    return list(data, len, pool);

  /* Is it a string with an implicit length?  */
  if (skel_char_type[(unsigned char) c] == type_name)
    return implicit_atom(data, len, pool);

  /* Otherwise, we assume it's a string with an explicit length;
     svn_skel__getsize will catch the error.  */
  else
    return explicit_atom(data, len, pool);
}