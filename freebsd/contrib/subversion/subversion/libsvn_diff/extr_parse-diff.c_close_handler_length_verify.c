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
struct length_verify_baton_t {int /*<<< orphan*/  inner; } ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_handler_length_verify(void *baton)
{
  struct length_verify_baton_t *lvb = baton;

  return svn_error_trace(svn_stream_close(lvb->inner));
}