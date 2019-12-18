#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {int bytes_max; int bytes_used; int /*<<< orphan*/  mutex; scalar_t__ values_used; scalar_t__ values_max; struct TYPE_4__* values; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ prefix_pool_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_UINT32_MAX ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prefix_pool_create(prefix_pool_t **prefix_pool,
                   apr_size_t bytes_max,
                   svn_boolean_t mutex_required,
                   apr_pool_t *result_pool)
{
  enum
    {
      /* With 56 byes of overhead under 64 bits, we will probably never get
       * substantially below this.  If we accidentally do, we will simply
       * run out of entries in the VALUES array before running out of
       * allocated memory. */
      ESTIMATED_BYTES_PER_ENTRY = 120
    };

  /* Number of entries we are going to support. */
  apr_size_t capacity = MIN(APR_UINT32_MAX,
                            bytes_max / ESTIMATED_BYTES_PER_ENTRY);

  /* Construct the result struct. */
  prefix_pool_t *result = apr_pcalloc(result_pool, sizeof(*result));
  result->map = svn_hash__make(result_pool);

  result->values = capacity
                 ? apr_pcalloc(result_pool, capacity * sizeof(const char *))
                 : NULL;
  result->values_max = (apr_uint32_t)capacity;
  result->values_used = 0;

  result->bytes_max = bytes_max;
  result->bytes_used = capacity * sizeof(svn_membuf_t);

  SVN_ERR(svn_mutex__init(&result->mutex, mutex_required, result_pool));

  /* Done. */
  *prefix_pool = result;
  return SVN_NO_ERROR;
}