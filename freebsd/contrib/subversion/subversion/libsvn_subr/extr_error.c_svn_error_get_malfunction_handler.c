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
typedef  int /*<<< orphan*/  svn_error_malfunction_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  malfunction_handler ; 

svn_error_malfunction_handler_t
svn_error_get_malfunction_handler(void)
{
  return malfunction_handler;
}