#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  encode_ucs4 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  svn_membuf__resize (TYPE_1__*,int) ; 

svn_error_t *
svn_utf__encode_ucs4_string(svn_membuf_t *buffer,
                            const apr_int32_t *ucs4str,
                            apr_size_t length,
                            apr_size_t *result_length)
{
  *result_length = 0;
  while (length-- > 0)
    SVN_ERR(encode_ucs4(buffer, *ucs4str++, result_length));
  svn_membuf__resize(buffer, *result_length + 1);
  ((char*)buffer->data)[*result_length] = '\0';
  return SVN_NO_ERROR;
}