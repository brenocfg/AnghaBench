#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_packed__int_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/ * first_int_stream; } ;
typedef  TYPE_1__ svn_packed__data_root_t ;

/* Variables and functions */

svn_packed__int_stream_t *
svn_packed__first_int_stream(svn_packed__data_root_t *root)
{
  return root->first_int_stream;
}