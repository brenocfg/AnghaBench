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
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton_t {int /*<<< orphan*/  writing_begun; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * output_revision (struct revision_baton_t*) ; 

__attribute__((used)) static svn_error_t *
close_revision(void *revision_baton)
{
  struct revision_baton_t *rb = revision_baton;

  /* If no node has yet flushed the revision, do it now. */
  if (! rb->writing_begun)
    return output_revision(rb);
  else
    return SVN_NO_ERROR;
}