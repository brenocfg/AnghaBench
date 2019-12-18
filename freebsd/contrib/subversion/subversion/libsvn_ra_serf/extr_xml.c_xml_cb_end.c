#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_8__ {scalar_t__ state_pool; struct TYPE_8__* prev; int /*<<< orphan*/  attrs; int /*<<< orphan*/  state; TYPE_4__* cdata; scalar_t__ custom_close; } ;
typedef  TYPE_1__ svn_ra_serf__xml_estate_t ;
struct TYPE_9__ {scalar_t__ waiting; TYPE_1__* free_states; TYPE_1__* current; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  baton; int /*<<< orphan*/  (* closed_cb ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/ * svn_stringbuf__morph_into_string (TYPE_4__*) ; 

__attribute__((used)) static svn_error_t *
xml_cb_end(svn_ra_serf__xml_context_t *xmlctx,
           const char *raw_name)
{
  svn_ra_serf__xml_estate_t *xes = xmlctx->current;

  if (xmlctx->waiting > 0)
    {
      xmlctx->waiting--;
      return SVN_NO_ERROR;
    }

  if (xes->custom_close)
    {
      const svn_string_t *cdata;

      if (xes->cdata)
        {
          cdata = svn_stringbuf__morph_into_string(xes->cdata);
#ifdef SVN_DEBUG
          /* We might toss the pool holding this structure, but it could also
             be within a parent pool. In any case, for safety's sake, disable
             the stringbuf against future Badness.  */
          xes->cdata->pool = NULL;
#endif
        }
      else
        cdata = NULL;

      START_CALLBACK(xmlctx);
      SVN_ERR(xmlctx->closed_cb(xes, xmlctx->baton, xes->state,
                                cdata, xes->attrs,
                                xmlctx->scratch_pool));
      END_CALLBACK(xmlctx);
      svn_pool_clear(xmlctx->scratch_pool);
    }

  /* Pop the state.  */
  xmlctx->current = xes->prev;

  /* ### not everything should go on the free state list. XES may go
     ### away with the state pool.  */
  xes->prev = xmlctx->free_states;
  xmlctx->free_states = xes;

  /* If there is a STATE_POOL, then toss it. This will get rid of as much
     memory as possible. Potentially the XES (if we didn't create a pool
     right away, then XES may be in a parent pool).  */
  if (xes->state_pool)
    svn_pool_destroy(xes->state_pool);

  return SVN_NO_ERROR;
}