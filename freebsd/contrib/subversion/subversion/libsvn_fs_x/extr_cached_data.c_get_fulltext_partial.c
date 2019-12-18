#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int start; int len; void* read; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ fulltext_baton_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* MIN (int,int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,void*) ; 

__attribute__((used)) static svn_error_t *
get_fulltext_partial(void **out,
                     const void *data,
                     apr_size_t data_len,
                     void *baton,
                     apr_pool_t *result_pool)
{
  fulltext_baton_t *fulltext_baton = baton;

  /* We cached the fulltext with an NUL appended to it. */
  apr_size_t fulltext_len = data_len - 1;

  /* Clip the copy range to what the fulltext size allows. */
  apr_size_t start = MIN(fulltext_baton->start, fulltext_len);
  fulltext_baton->read = MIN(fulltext_len - start, fulltext_baton->len);

  /* Copy the data to the output buffer and be done. */
  memcpy(fulltext_baton->buffer, (const char *)data + start,
         fulltext_baton->read);

  return SVN_NO_ERROR;
}