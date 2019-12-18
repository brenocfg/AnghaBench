#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  special; int /*<<< orphan*/  pool; void* author; int /*<<< orphan*/  date; void* revision; void* executable_val; void* keywords_val; TYPE_1__* edit_baton; void* eol_style_val; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  ignore_keywords; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 void* svn_string_dup (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
change_file_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;

  if (! value)
    return SVN_NO_ERROR;

  /* Store only the magic three properties. */
  if (strcmp(name, SVN_PROP_EOL_STYLE) == 0)
    fb->eol_style_val = svn_string_dup(value, fb->pool);

  else if (! fb->edit_baton->ignore_keywords &&
           strcmp(name, SVN_PROP_KEYWORDS) == 0)
    fb->keywords_val = svn_string_dup(value, fb->pool);

  else if (strcmp(name, SVN_PROP_EXECUTABLE) == 0)
    fb->executable_val = svn_string_dup(value, fb->pool);

  /* Try to fill out the baton's keywords-structure too. */
  else if (strcmp(name, SVN_PROP_ENTRY_COMMITTED_REV) == 0)
    fb->revision = apr_pstrdup(fb->pool, value->data);

  else if (strcmp(name, SVN_PROP_ENTRY_COMMITTED_DATE) == 0)
    SVN_ERR(svn_time_from_cstring(&fb->date, value->data, fb->pool));

  else if (strcmp(name, SVN_PROP_ENTRY_LAST_AUTHOR) == 0)
    fb->author = apr_pstrdup(fb->pool, value->data);

  else if (strcmp(name, SVN_PROP_SPECIAL) == 0)
    fb->special = TRUE;

  return SVN_NO_ERROR;
}