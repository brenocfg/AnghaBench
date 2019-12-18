#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_9__ {int offset; TYPE_1__* value; } ;
typedef  TYPE_3__ prop_read_baton_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int len; char const* data; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_2__*,char const) ; 
 TYPE_2__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
readline_prop(void *baton, svn_stringbuf_t **line, const char **eol_str,
              svn_boolean_t *eof, apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  prop_read_baton_t *b = baton;
  svn_stringbuf_t *str = NULL;
  const char *c;
  svn_boolean_t found_eof;

  if ((apr_uint64_t)b->offset >= (apr_uint64_t)b->value->len)
    {
      *eol_str = NULL;
      *eof = TRUE;
      *line = NULL;
      return SVN_NO_ERROR;
    }

  /* Read bytes into STR up to and including, but not storing,
   * the next EOL sequence. */
  *eol_str = NULL;
  found_eof = FALSE;
  do
    {
      c = b->value->data + b->offset;
      b->offset++;

      if (*c == '\0')
        {
          found_eof = TRUE;
          break;
        }
      else if (*c == '\n')
        {
          *eol_str = "\n";
        }
      else if (*c == '\r')
        {
          *eol_str = "\r";
          if (*(c + 1) == '\n')
            {
              *eol_str = "\r\n";
              b->offset++;
            }
        }
      else
        {
          if (str == NULL)
            str = svn_stringbuf_create_ensure(80, result_pool);
          svn_stringbuf_appendbyte(str, *c);
        }

      if (*eol_str)
        break;
    }
  while (c < b->value->data + b->value->len);

  if (eof)
    *eof = found_eof && !(str && str->len > 0);
  *line = str;

  return SVN_NO_ERROR;
}