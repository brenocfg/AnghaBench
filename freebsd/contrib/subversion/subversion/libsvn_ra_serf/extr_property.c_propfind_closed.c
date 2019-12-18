#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {char const* depth; char* path; int /*<<< orphan*/ * ps_props; int /*<<< orphan*/  prop_func_baton; int /*<<< orphan*/  (* prop_func ) (int /*<<< orphan*/ ,char const*,char const*,char const*,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ propfind_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int COLLECTION ; 
 char const* D_ ; 
 int HREF ; 
 int HREF_VALUE ; 
 int MULTISTATUS ; 
 int PROPSTAT ; 
 int PROPVAL ; 
 int RESPONSE ; 
 int STATUS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int parse_status_code (char*) ; 
 int /*<<< orphan*/  set_ns_prop (int /*<<< orphan*/ *,char const*,char const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char const*,char*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,char const*,char const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_base64_decode_string (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_gather_since (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_note (int /*<<< orphan*/ *,int,char*,char const*) ; 
 TYPE_1__* svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 char* svn_urlpath__canonicalize (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
propfind_closed(svn_ra_serf__xml_estate_t *xes,
                void *baton,
                int leaving_state,
                const svn_string_t *cdata,
                apr_hash_t *attrs,
                apr_pool_t *scratch_pool)
{
  propfind_context_t *ctx = baton;

  if (leaving_state == MULTISTATUS)
    {
      /* We've gathered all the data from the reponse. Add this item
         onto the "done list". External callers will then know this
         request has been completed (tho stray response bytes may still
         arrive).  */
    }
  else if (leaving_state == HREF)
    {
      const char *path;

      if (strcmp(ctx->depth, "1") == 0)
        path = svn_urlpath__canonicalize(cdata->data, scratch_pool);
      else
        path = ctx->path;

      svn_ra_serf__xml_note(xes, RESPONSE, "path", path);

      SVN_ERR(ctx->prop_func(ctx->prop_func_baton,
                             path,
                             D_, "href",
                             cdata, scratch_pool));
    }
  else if (leaving_state == COLLECTION)
    {
      svn_ra_serf__xml_note(xes, PROPVAL, "altvalue", "collection");
    }
  else if (leaving_state == HREF_VALUE)
    {
      svn_ra_serf__xml_note(xes, PROPVAL, "altvalue", cdata->data);
    }
  else if (leaving_state == STATUS)
    {
      /* Parse the status field, and remember if this is a property
         that we wish to ignore.  (Typically, if it's not a 200, the
         status will be 404 to indicate that a property we
         specifically requested from the server doesn't exist.)  */
      apr_int64_t status = parse_status_code(cdata->data);
      if (status != 200)
        svn_ra_serf__xml_note(xes, PROPSTAT, "ignore-prop", "*");
    }
  else if (leaving_state == PROPVAL)
    {
      const char *encoding;
      const svn_string_t *val_str;
      const char *ns;
      const char *name;
      const char *altvalue;

      if ((altvalue = svn_hash_gets(attrs, "altvalue")) != NULL)
        {
          val_str = svn_string_create(altvalue, scratch_pool);
        }
      else if ((encoding = svn_hash_gets(attrs, "V:encoding")) != NULL)
        {
          if (strcmp(encoding, "base64") != 0)
            return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA,
                                     NULL,
                                     _("Got unrecognized encoding '%s'"),
                                     encoding);

          /* Decode into the right pool.  */
          val_str = svn_base64_decode_string(cdata, scratch_pool);
        }
      else
        {
          /* Copy into the right pool.  */
          val_str = cdata;
        }

      /* The current path sits on the RESPONSE state.

         Now, it would be nice if we could, at this point, know that
         the status code for this property indicated a problem -- then
         we could simply bail out here and ignore the property.
         Sadly, though, we might get the status code *after* we get
         the property value.  So we'll carry on with our processing
         here, setting the property and value as expected.  Once we
         know for sure the status code associate with the property,
         we'll decide its fate.  */

      ns = svn_hash_gets(attrs, "ns");
      name = svn_hash_gets(attrs, "name");

      set_ns_prop(ctx->ps_props, ns, name, val_str,
                  apr_hash_pool_get(ctx->ps_props));
    }
  else
    {
      apr_hash_t *gathered;

      SVN_ERR_ASSERT(leaving_state == PROPSTAT);

      gathered = svn_ra_serf__xml_gather_since(xes, RESPONSE);

      /* If we've squirreled away a note that says we want to ignore
         these properties, we'll do so.  Otherwise, we need to copy
         them from the temporary hash into the ctx->ret_props hash. */
      if (! svn_hash_gets(gathered, "ignore-prop"))
        {
          apr_hash_index_t *hi_ns;
          const char *path;
          apr_pool_t *iterpool = svn_pool_create(scratch_pool);


          path = svn_hash_gets(gathered, "path");
          if (!path)
            path = ctx->path;

          for (hi_ns = apr_hash_first(scratch_pool, ctx->ps_props);
               hi_ns;
               hi_ns = apr_hash_next(hi_ns))
            {
              const char *ns = apr_hash_this_key(hi_ns);
              apr_hash_t *props = apr_hash_this_val(hi_ns);
              apr_hash_index_t *hi_prop;

              svn_pool_clear(iterpool);

              for (hi_prop = apr_hash_first(iterpool, props);
                   hi_prop;
                   hi_prop = apr_hash_next(hi_prop))
                {
                  const char *name = apr_hash_this_key(hi_prop);
                  const svn_string_t *value = apr_hash_this_val(hi_prop);

                  SVN_ERR(ctx->prop_func(ctx->prop_func_baton, path,
                                         ns, name, value, iterpool));
                }
            }

          svn_pool_destroy(iterpool);
        }

      ctx->ps_props = NULL; /* Allocated in PROPSTAT state pool */
    }

  return SVN_NO_ERROR;
}