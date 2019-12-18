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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * normalize_cstring (int*,char const*,int const,int,int,TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_membuf__create (TYPE_1__*,int const,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_utf__is_normalized(const char *string, apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_membuf_t buffer;
  apr_size_t result_length;
  const apr_size_t length = strlen(string);
  svn_membuf__create(&buffer, length * sizeof(apr_int32_t), scratch_pool);
  err = normalize_cstring(&result_length, string, length,
                          FALSE, FALSE, &buffer);
  if (err)
    {
      svn_error_clear(err);
      return FALSE;
    }
  return (length == result_length && 0 == strcmp(string, buffer.data));
}