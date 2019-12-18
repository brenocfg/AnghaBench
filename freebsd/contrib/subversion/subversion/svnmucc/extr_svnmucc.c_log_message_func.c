#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct log_message_baton {char* log_message; TYPE_1__* ctx; scalar_t__ non_interactive; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_8__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_INSUFFICIENT_ARGS ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline__edit_string_externally (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_string_create (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_translate_string2 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
log_message_func(const char **log_msg,
                 const char **tmp_file,
                 const apr_array_header_t *commit_items,
                 void *baton,
                 apr_pool_t *pool)
{
  struct log_message_baton *lmb = baton;

  *tmp_file = NULL;

  if (lmb->log_message)
    {
      svn_string_t *message = svn_string_create(lmb->log_message, pool);

      SVN_ERR_W(svn_subst_translate_string2(&message, NULL, NULL,
                                            message, NULL, FALSE,
                                            pool, pool),
                _("Error normalizing log message to internal format"));

      *log_msg = message->data;

      return SVN_NO_ERROR;
    }

  if (lmb->non_interactive)
    {
      return svn_error_create(SVN_ERR_CL_INSUFFICIENT_ARGS, NULL,
                              _("Cannot invoke editor to get log message "
                                "when non-interactive"));
    }
  else
    {
      svn_string_t *msg = svn_string_create("", pool);

      SVN_ERR(svn_cmdline__edit_string_externally(
                      &msg, NULL, NULL, "", msg, "svnmucc-commit",
                      lmb->ctx->config, TRUE, NULL, pool));

      if (msg && msg->data)
        *log_msg = msg->data;
      else
        *log_msg = NULL;

      return SVN_NO_ERROR;
    }
}