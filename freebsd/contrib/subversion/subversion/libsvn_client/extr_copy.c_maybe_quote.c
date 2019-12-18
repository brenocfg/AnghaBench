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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  apr_tokenize_to_argv (char const*,char***,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char const) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
maybe_quote(const char *value,
            apr_pool_t *result_pool)
{
  apr_status_t status;
  char **argv;

  status = apr_tokenize_to_argv(value, &argv, result_pool);

  if (!status && argv[0] && !argv[1] && strcmp(argv[0], value) == 0)
    return apr_pstrdup(result_pool, value);

  {
    svn_stringbuf_t *sb = svn_stringbuf_create_empty(result_pool);
    const char *c;

    svn_stringbuf_appendbyte(sb, '\"');

    for (c = value; *c; c++)
      {
        if (*c == '\\' || *c == '\"' || *c == '\'')
          svn_stringbuf_appendbyte(sb, '\\');

        svn_stringbuf_appendbyte(sb, *c);
      }

    svn_stringbuf_appendbyte(sb, '\"');

#ifdef SVN_DEBUG
    status = apr_tokenize_to_argv(sb->data, &argv, result_pool);

    SVN_ERR_ASSERT_NO_RETURN(!status && argv[0] && !argv[1]
                             && !strcmp(argv[0], value));
#endif

    return sb->data;
  }
}