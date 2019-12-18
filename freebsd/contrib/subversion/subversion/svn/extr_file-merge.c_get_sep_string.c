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
 int LINE_DISPLAY_WIDTH ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
get_sep_string(apr_pool_t *result_pool)
{
  int line_width = LINE_DISPLAY_WIDTH;
  int i;
  svn_stringbuf_t *buf;

  buf = svn_stringbuf_create_empty(result_pool);
  for (i = 0; i < line_width; i++)
    svn_stringbuf_appendbyte(buf, '-');
  svn_stringbuf_appendbyte(buf, '+');
  for (i = 0; i < line_width; i++)
    svn_stringbuf_appendbyte(buf, '-');
  svn_stringbuf_appendbyte(buf, '\n');

  return buf->data;
}