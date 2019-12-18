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
typedef  int svn_boolean_t ;
struct stringbuf_stream_baton {scalar_t__ amt_read; TYPE_1__* str; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
data_available_handler_stringbuf(void *baton, svn_boolean_t *data_available)
{
  struct stringbuf_stream_baton *btn = baton;

  *data_available = ((btn->str->len - btn->amt_read) > 0);
  return SVN_NO_ERROR;
}