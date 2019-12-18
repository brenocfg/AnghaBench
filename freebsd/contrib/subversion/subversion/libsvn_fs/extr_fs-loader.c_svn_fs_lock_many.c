#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_10__ {char* token; } ;
typedef  TYPE_3__ svn_fs_lock_target_t ;
typedef  int /*<<< orphan*/ * (* svn_fs_lock_callback_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_8__ {int /*<<< orphan*/ * (* lock ) (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_BAD_LOCK_TOKEN ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  SVN_ERR_XML_UNESCAPABLE_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ctype_isascii (char const) ; 
 scalar_t__ svn_ctype_iscntrl (char const) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  svn_xml_is_xml_safe (char const*,int) ; 

svn_error_t *
svn_fs_lock_many(svn_fs_t *fs,
                 apr_hash_t *targets,
                 const char *comment,
                 svn_boolean_t is_dav_comment,
                 apr_time_t expiration_date,
                 svn_boolean_t steal_lock,
                 svn_fs_lock_callback_t lock_callback,
                 void *lock_baton,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  apr_hash_t *ok_targets = apr_hash_make(scratch_pool);
  svn_error_t *err, *cb_err = SVN_NO_ERROR;

  /* Enforce that the comment be xml-escapable. */
  if (comment)
    if (! svn_xml_is_xml_safe(comment, strlen(comment)))
      return svn_error_create(SVN_ERR_XML_UNESCAPABLE_DATA, NULL,
                              _("Lock comment contains illegal characters"));

  if (expiration_date < 0)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
              _("Negative expiration date passed to svn_fs_lock"));

  /* Enforce that the token be an XML-safe URI. */
  for (hi = apr_hash_first(scratch_pool, targets); hi; hi = apr_hash_next(hi))
    {
      const svn_fs_lock_target_t *target = apr_hash_this_val(hi);

      err = SVN_NO_ERROR;
      if (target->token)
        {
          const char *c;


          if (strncmp(target->token, "opaquelocktoken:", 16))
            err = svn_error_createf(SVN_ERR_FS_BAD_LOCK_TOKEN, NULL,
                                    _("Lock token URI '%s' has bad scheme; "
                                      "expected '%s'"),
                                    target->token, "opaquelocktoken");

          if (!err)
            {
              for (c = target->token; *c && !err; c++)
                if (! svn_ctype_isascii(*c) || svn_ctype_iscntrl(*c))
                  err = svn_error_createf(
                          SVN_ERR_FS_BAD_LOCK_TOKEN, NULL,
                          _("Lock token '%s' is not ASCII or is a "
                            "control character at byte %u"),
                          target->token,
                          (unsigned)(c - target->token));

              /* strlen(token) == c - token. */
              if (!err && !svn_xml_is_xml_safe(target->token,
                                               c - target->token))
                err = svn_error_createf(
                            SVN_ERR_FS_BAD_LOCK_TOKEN, NULL,
                            _("Lock token URI '%s' is not XML-safe"),
                            target->token);
            }
        }

      if (err)
        {
          if (!cb_err && lock_callback)
            cb_err = lock_callback(lock_baton, apr_hash_this_key(hi),
                                   NULL, err, scratch_pool);
          svn_error_clear(err);
        }
      else
        svn_hash_sets(ok_targets, apr_hash_this_key(hi), target);
    }

  if (!apr_hash_count(ok_targets))
    return svn_error_trace(cb_err);

  err = fs->vtable->lock(fs, ok_targets, comment, is_dav_comment,
                         expiration_date, steal_lock,
                         lock_callback, lock_baton,
                         result_pool, scratch_pool);

  if (err && cb_err)
    svn_error_compose(err, cb_err);
  else if (!err)
    err = cb_err;

  return svn_error_trace(err);
}