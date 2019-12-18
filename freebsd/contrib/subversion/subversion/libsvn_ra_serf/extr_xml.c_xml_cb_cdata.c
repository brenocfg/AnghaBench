#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ waiting; int /*<<< orphan*/  scratch_pool; TYPE_3__* current; int /*<<< orphan*/  baton; int /*<<< orphan*/  (* cdata_cb ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_CALLBACK (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
xml_cb_cdata(svn_ra_serf__xml_context_t *xmlctx,
             const char *data,
             apr_size_t len)
{
  /* If we are waiting for a closing tag, then we are uninterested in
     the cdata. Just return.  */
  if (xmlctx->waiting > 0)
    return SVN_NO_ERROR;

  /* If the current state is collecting cdata, then copy the cdata.  */
  if (xmlctx->current->cdata != NULL)
    {
      svn_stringbuf_appendbytes(xmlctx->current->cdata, data, len);
    }
  /* ... else if a CDATA_CB has been supplied, then invoke it for
     all states.  */
  else if (xmlctx->cdata_cb != NULL)
    {
      START_CALLBACK(xmlctx);
      SVN_ERR(xmlctx->cdata_cb(xmlctx->current,
                               xmlctx->baton,
                               xmlctx->current->state,
                               data, len,
                               xmlctx->scratch_pool));
      END_CALLBACK(xmlctx);
      svn_pool_clear(xmlctx->scratch_pool);
    }

  return SVN_NO_ERROR;
}