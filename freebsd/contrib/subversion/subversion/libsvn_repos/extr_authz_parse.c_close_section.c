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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {void* in_aliases; void* in_groups; int /*<<< orphan*/ * current_acl; int /*<<< orphan*/ * section; } ;
typedef  TYPE_2__ ctor_baton_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_section(void *baton, svn_stringbuf_t *section)
{
  ctor_baton_t *const cb = baton;

  SVN_ERR_ASSERT(0 == strcmp(cb->section, section->data));
  cb->section = NULL;
  cb->current_acl = NULL;
  cb->in_groups = FALSE;
  cb->in_aliases = FALSE;
  return SVN_NO_ERROR;
}