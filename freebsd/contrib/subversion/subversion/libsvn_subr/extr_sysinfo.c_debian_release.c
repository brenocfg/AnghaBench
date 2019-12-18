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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* read_file_contents (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stringbuf_first_line_only (TYPE_1__*) ; 

__attribute__((used)) static const char *
debian_release(apr_pool_t *pool)
{
  svn_stringbuf_t *buffer = read_file_contents("/etc/debian_version", pool);
  if (!buffer)
      return NULL;

  stringbuf_first_line_only(buffer);
  return apr_pstrcat(pool, "Debian ", buffer->data, SVN_VA_NULL);
}