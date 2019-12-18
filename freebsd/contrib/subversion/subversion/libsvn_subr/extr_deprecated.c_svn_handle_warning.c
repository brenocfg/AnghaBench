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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void
svn_handle_warning(FILE *stream, svn_error_t *err)
{
  svn_handle_warning2(stream, err, "svn: ");
}