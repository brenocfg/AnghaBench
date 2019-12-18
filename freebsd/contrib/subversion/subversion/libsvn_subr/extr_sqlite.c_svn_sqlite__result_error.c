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
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ svn_sqlite__context_t ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ ,char const*,int) ; 

void
svn_sqlite__result_error(svn_sqlite__context_t *sctx, const char *msg, int num)
{
  sqlite3_result_error(sctx->context, msg, num);
}