#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_UNEXPECTED_END ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
read_one_byte(unsigned char *byte, svn_stream_t *stream)
{
  char c;
  apr_size_t len = 1;

  SVN_ERR(svn_stream_read_full(stream, &c, &len));
  if (len == 0)
    return svn_error_create(SVN_ERR_SVNDIFF_UNEXPECTED_END, NULL,
                            _("Unexpected end of svndiff input"));
  *byte = (unsigned char) c;
  return SVN_NO_ERROR;
}