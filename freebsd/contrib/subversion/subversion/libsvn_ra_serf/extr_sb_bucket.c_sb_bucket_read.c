#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct sbb_baton {char* holding; scalar_t__ hold_len; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  spillbuf; } ;
struct TYPE_3__ {struct sbb_baton* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOF ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_spillbuf__read (char const**,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
sb_bucket_read(serf_bucket_t *bucket, apr_size_t requested,
               const char **data, apr_size_t *len)
{
  struct sbb_baton *sbb = bucket->data;
  svn_error_t *err;

  if (sbb->holding)
    {
      *data = sbb->holding;

      if (requested < sbb->hold_len)
        {
          *len = requested;
          sbb->holding += requested;
          sbb->hold_len -= requested;
          return APR_SUCCESS;
        }

      /* Return whatever we're holding, and then forget (consume) it.  */
      *len = sbb->hold_len;
      sbb->holding = NULL;
      return APR_SUCCESS;
    }

  err = svn_spillbuf__read(data, len, sbb->spillbuf, sbb->scratch_pool);
  svn_pool_clear(sbb->scratch_pool);

  /* ### do something with this  */
  svn_error_clear(err);

  /* The spillbuf may have returned more than requested. Stash any extra
     into our holding area.  */
  if (requested < *len)
    {
      sbb->holding = *data + requested;
      sbb->hold_len = *len - requested;
      *len = requested;
    }

  return *data == NULL ? APR_EOF : APR_SUCCESS;
}