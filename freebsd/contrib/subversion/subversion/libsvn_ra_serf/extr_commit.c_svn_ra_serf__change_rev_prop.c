#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_22__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_23__ {int /*<<< orphan*/  rev_stub; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
struct TYPE_24__ {char const* name; int /*<<< orphan*/  const* value; } ;
typedef  TYPE_3__ svn_prop_t ;
struct TYPE_25__ {scalar_t__ apr_err; struct TYPE_25__* child; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_26__ {char const* path; void* prop_changes; void* old_props; int /*<<< orphan*/  base_revision; int /*<<< orphan*/ * commit_ctx; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_5__ proppatch_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (scalar_t__) ; 
 scalar_t__ SVN_ERR_FS_PROP_BASEVALUE_MISMATCH ; 
 scalar_t__ SVN_ERR_RA_DAV_PRECONDITION_FAILED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 scalar_t__ SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_2__*) ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* proppatch_resource (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_hash_sets (void*,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__fetch_dav_prop (char const**,TYPE_2__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__has_capability (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__rev_prop (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__change_rev_prop(svn_ra_session_t *ra_session,
                             svn_revnum_t rev,
                             const char *name,
                             const svn_string_t *const *old_value_p,
                             const svn_string_t *value,
                             apr_pool_t *pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;
  proppatch_context_t *proppatch_ctx;
  const char *proppatch_target;
  const svn_string_t *tmp_old_value;
  svn_boolean_t atomic_capable = FALSE;
  svn_prop_t *prop;
  svn_error_t *err;

  if (old_value_p || !value)
    SVN_ERR(svn_ra_serf__has_capability(ra_session, &atomic_capable,
                                        SVN_RA_CAPABILITY_ATOMIC_REVPROPS,
                                        pool));

  if (old_value_p)
    {
      /* How did you get past the same check in svn_ra_change_rev_prop2()? */
      SVN_ERR_ASSERT(atomic_capable);
    }
  else if (! value && atomic_capable)
    {
      svn_string_t *old_value;
      /* mod_dav_svn doesn't report a failure when a property delete fails. The
         atomic revprop change behavior is a nice workaround, to allow getting
         access to the error anyway.

         Somehow the mod_dav maintainers think that returning an error from
         mod_dav's property delete is an RFC violation.
         See https://issues.apache.org/bugzilla/show_bug.cgi?id=53525 */

      SVN_ERR(svn_ra_serf__rev_prop(ra_session, rev, name, &old_value,
                                    pool));

      if (!old_value)
        return SVN_NO_ERROR; /* Nothing to delete */

      /* The api expects a double const pointer. Let's make one */
      tmp_old_value = old_value;
      old_value_p = &tmp_old_value;
    }

  if (SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session))
    {
      proppatch_target = apr_psprintf(pool, "%s/%ld", session->rev_stub, rev);
    }
  else
    {
      const char *vcc_url;

      SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session, pool));

      SVN_ERR(svn_ra_serf__fetch_dav_prop(&proppatch_target,
                                          session, vcc_url, rev, "href",
                                          pool, pool));
    }

  /* PROPPATCH our log message and pass it along.  */
  proppatch_ctx = apr_pcalloc(pool, sizeof(*proppatch_ctx));
  proppatch_ctx->pool = pool;
  proppatch_ctx->commit_ctx = NULL; /* No lock headers */
  proppatch_ctx->path = proppatch_target;
  proppatch_ctx->prop_changes = apr_hash_make(pool);
  proppatch_ctx->base_revision = SVN_INVALID_REVNUM;

  if (old_value_p)
    {
      prop = apr_palloc(pool, sizeof (*prop));

      prop->name = name;
      prop->value = *old_value_p;

      proppatch_ctx->old_props = apr_hash_make(pool);
      svn_hash_sets(proppatch_ctx->old_props, prop->name, prop);
    }

  prop = apr_palloc(pool, sizeof (*prop));

  prop->name = name;
  prop->value = value;
  svn_hash_sets(proppatch_ctx->prop_changes, prop->name, prop);

  err = proppatch_resource(session, proppatch_ctx, pool);

  /* Use specific error code for old property value mismatch.
     Use loop to provide the right result with tracing */
  if (err && err->apr_err == SVN_ERR_RA_DAV_PRECONDITION_FAILED)
    {
      svn_error_t *e = err;

      while (e && e->apr_err == SVN_ERR_RA_DAV_PRECONDITION_FAILED)
        {
          e->apr_err = SVN_ERR_FS_PROP_BASEVALUE_MISMATCH;
          e = e->child;
        }
    }

  return svn_error_trace(err);
}