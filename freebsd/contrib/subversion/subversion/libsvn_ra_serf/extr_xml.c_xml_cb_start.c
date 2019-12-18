#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* ns; scalar_t__ from_state; char* name; char** collect_attrs; scalar_t__ to_state; scalar_t__ custom_close; scalar_t__ collect_cdata; } ;
typedef  TYPE_1__ svn_ra_serf__xml_transition_t ;
struct TYPE_18__ {void* xmlns; void* name; } ;
struct TYPE_15__ {scalar_t__ state; TYPE_8__ tag; struct TYPE_15__* prev; int /*<<< orphan*/  ns_list; scalar_t__ custom_close; int /*<<< orphan*/  attrs; int /*<<< orphan*/  cdata; int /*<<< orphan*/ * state_pool; } ;
typedef  TYPE_2__ svn_ra_serf__xml_estate_t ;
struct TYPE_16__ {scalar_t__ waiting; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; int /*<<< orphan*/  (* opened_cb ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,TYPE_8__*,int /*<<< orphan*/ ) ;TYPE_2__* current; TYPE_1__* ttable; } ;
typedef  TYPE_3__ svn_ra_serf__xml_context_t ;
struct TYPE_17__ {char const* name; char const* xmlns; } ;
typedef  TYPE_4__ svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  END_CALLBACK (TYPE_3__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_XML_ATTRIB_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_XML_UNEXPECTED_ELEMENT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ XML_STATE_INITIAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  define_namespaces (int /*<<< orphan*/ *,char const* const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  expand_ns (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lazy_create_pool ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,void*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 char* svn_xml_get_attr_value (char const*,char const* const*) ; 
 int /*<<< orphan*/ * xes_pool (TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
xml_cb_start(svn_ra_serf__xml_context_t *xmlctx,
             const char *raw_name,
             const char *const *attrs)
{
  svn_ra_serf__xml_estate_t *current = xmlctx->current;
  svn_ra_serf__dav_props_t elemname;
  const svn_ra_serf__xml_transition_t *scan;
  apr_pool_t *new_pool;
  svn_ra_serf__xml_estate_t *new_xes;

  /* If we're waiting for an element to close, then just ignore all
     other element-opens.  */
  if (xmlctx->waiting > 0)
    {
      xmlctx->waiting++;
      return SVN_NO_ERROR;
    }

  /* Look for xmlns: attributes. Lazily create the state pool if any
     were found.  */
  define_namespaces(&current->ns_list, attrs, lazy_create_pool, current);

  expand_ns(&elemname, current->ns_list, raw_name);

  for (scan = xmlctx->ttable; scan->ns != NULL; ++scan)
    {
      if (scan->from_state != current->state)
        continue;

      /* Wildcard tag match.  */
      if (*scan->name == '*')
        break;

      /* Found a specific transition.  */
      if (strcmp(elemname.name, scan->name) == 0
          && strcmp(elemname.xmlns, scan->ns) == 0)
        break;
    }
  if (scan->ns == NULL)
    {
      if (current->state == XML_STATE_INITIAL)
        {
          return svn_error_createf(
                        SVN_ERR_XML_UNEXPECTED_ELEMENT, NULL,
                        _("XML Parsing failed: Unexpected root element '%s'"),
                        elemname.name);
        }

      xmlctx->waiting++; /* Start waiting for the close tag */
      return SVN_NO_ERROR;
    }

  /* We should not be told to collect cdata if the closed_cb will not
     be called.  */
  SVN_ERR_ASSERT(!scan->collect_cdata || scan->custom_close);

  /* Found a transition. Make it happen.  */

  /* ### todo. push state  */

  /* ### how to use free states?  */
  /* This state should be allocated in the extent pool. If we will be
     collecting information for this state, then construct a subpool.

     ### potentially optimize away the subpool if none of the
     ### attributes are present. subpools are cheap, tho...  */
  new_pool = xes_pool(current);
  if (scan->collect_cdata || scan->collect_attrs[0])
    {
      new_pool = svn_pool_create(new_pool);

      /* Prep the new state.  */
      new_xes = apr_pcalloc(new_pool, sizeof(*new_xes));
      new_xes->state_pool = new_pool;

      /* If we're supposed to collect cdata, then set up a buffer for
         this. The existence of this buffer will instruct our cdata
         callback to collect the cdata.  */
      if (scan->collect_cdata)
        new_xes->cdata = svn_stringbuf_create_empty(new_pool);

      if (scan->collect_attrs[0] != NULL)
        {
          const char *const *saveattr = &scan->collect_attrs[0];

          new_xes->attrs = apr_hash_make(new_pool);
          for (; *saveattr != NULL; ++saveattr)
            {
              const char *name;
              const char *value;

              if (**saveattr == '?')
                {
                  name = *saveattr + 1;
                  value = svn_xml_get_attr_value(name, attrs);
                }
              else
                {
                  name = *saveattr;
                  value = svn_xml_get_attr_value(name, attrs);
                  if (value == NULL)
                    return svn_error_createf(
                                SVN_ERR_XML_ATTRIB_NOT_FOUND,
                                NULL,
                                _("Missing XML attribute '%s' on '%s' element"),
                                name, scan->name);
                }

              if (value)
                svn_hash_sets(new_xes->attrs, name,
                              apr_pstrdup(new_pool, value));
            }
        }
    }
  else
    {
      /* Prep the new state.  */
      new_xes = apr_pcalloc(new_pool, sizeof(*new_xes));
      /* STATE_POOL remains NULL.  */
    }

  /* Some basic copies to set up the new estate.  */
  new_xes->state = scan->to_state;
  new_xes->tag.name = apr_pstrdup(new_pool, elemname.name);
  new_xes->tag.xmlns = apr_pstrdup(new_pool, elemname.xmlns);
  new_xes->custom_close = scan->custom_close;

  /* Start with the parent's namespace set.  */
  new_xes->ns_list = current->ns_list;

  /* The new state is prepared. Make it current.  */
  new_xes->prev = current;
  xmlctx->current = new_xes;

  if (xmlctx->opened_cb)
    {
      START_CALLBACK(xmlctx);
      SVN_ERR(xmlctx->opened_cb(new_xes, xmlctx->baton,
                                new_xes->state, &new_xes->tag,
                                xmlctx->scratch_pool));
      END_CALLBACK(xmlctx);
      svn_pool_clear(xmlctx->scratch_pool);
    }

  return SVN_NO_ERROR;
}