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
struct TYPE_2__ {char const** data; size_t next_slot; int context_size; int /*<<< orphan*/  total_writes; int /*<<< orphan*/ * len; } ;
typedef  TYPE_1__ context_saver_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
context_saver_stream_write(void *baton,
                           const char *data,
                           apr_size_t *len)
{
  context_saver_t *cs = baton;
  cs->data[cs->next_slot] = data;
  cs->len[cs->next_slot] = *len;
  cs->next_slot = (cs->next_slot + 1) % cs->context_size;
  cs->total_writes++;
  return SVN_NO_ERROR;
}