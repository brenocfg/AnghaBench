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
struct TYPE_4__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* next_line (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char const*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

const char *
svn_cmdline__indent_string(const char *str,
                           const char *indent,
                           apr_pool_t *pool)
{
  svn_stringbuf_t *out = svn_stringbuf_create_empty(pool);
  const char *line;

  while ((line = next_line(&str, pool)))
    {
      svn_stringbuf_appendcstr(out, indent);
      svn_stringbuf_appendcstr(out, line);
    }
  return out->data;
}