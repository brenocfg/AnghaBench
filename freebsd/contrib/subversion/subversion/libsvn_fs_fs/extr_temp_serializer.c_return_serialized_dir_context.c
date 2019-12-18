#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; void* data; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ dir_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
return_serialized_dir_context(svn_temp_serializer__context_t *context,
                              void **data,
                              apr_size_t *data_len,
                              svn_boolean_t overprovision)
{
  svn_stringbuf_t *serialized = svn_temp_serializer__get(context);

  *data = serialized->data;
  *data_len = overprovision ? serialized->blocksize : serialized->len;
  ((dir_data_t *)serialized->data)->len = serialized->len;

  return SVN_NO_ERROR;
}