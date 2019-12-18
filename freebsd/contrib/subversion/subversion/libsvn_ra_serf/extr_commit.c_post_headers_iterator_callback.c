#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vtxn_root_stub; int /*<<< orphan*/  vtxn_stub; int /*<<< orphan*/  txn_root_stub; int /*<<< orphan*/  txn_stub; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_5__ {TYPE_3__* commit_ctx; } ;
typedef  TYPE_2__ post_response_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; void* txn_root_url; void* txn_url; TYPE_1__* session; } ;
typedef  TYPE_3__ commit_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_TXN_NAME_HEADER ; 
 int /*<<< orphan*/  SVN_DAV_VTXN_NAME_HEADER ; 
 scalar_t__ svn_cstring_casecmp (char const*,int /*<<< orphan*/ ) ; 
 void* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
post_headers_iterator_callback(void *baton,
                               const char *key,
                               const char *val)
{
  post_response_ctx_t *prc = baton;
  commit_context_t *prc_cc = prc->commit_ctx;
  svn_ra_serf__session_t *sess = prc_cc->session;

  /* If we provided a UUID to the POST request, we should get back
     from the server an SVN_DAV_VTXN_NAME_HEADER header; otherwise we
     expect the SVN_DAV_TXN_NAME_HEADER.  We certainly don't expect to
     see both. */

  if (svn_cstring_casecmp(key, SVN_DAV_TXN_NAME_HEADER) == 0)
    {
      /* Build out txn and txn-root URLs using the txn name we're
         given, and store the whole lot of it in the commit context.  */
      prc_cc->txn_url =
        svn_path_url_add_component2(sess->txn_stub, val, prc_cc->pool);
      prc_cc->txn_root_url =
        svn_path_url_add_component2(sess->txn_root_stub, val, prc_cc->pool);
    }

  if (svn_cstring_casecmp(key, SVN_DAV_VTXN_NAME_HEADER) == 0)
    {
      /* Build out vtxn and vtxn-root URLs using the vtxn name we're
         given, and store the whole lot of it in the commit context.  */
      prc_cc->txn_url =
        svn_path_url_add_component2(sess->vtxn_stub, val, prc_cc->pool);
      prc_cc->txn_root_url =
        svn_path_url_add_component2(sess->vtxn_root_stub, val, prc_cc->pool);
    }

  return 0;
}