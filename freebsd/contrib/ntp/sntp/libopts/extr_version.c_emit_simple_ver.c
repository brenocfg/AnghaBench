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
struct TYPE_3__ {int /*<<< orphan*/  pzUsageTitle; int /*<<< orphan*/  pzCopyright; int /*<<< orphan*/  pzFullVersion; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  emit_first_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_simple_ver(tOptions * o, FILE * fp)
{
    emit_first_line(fp, o->pzFullVersion, o->pzCopyright, o->pzUsageTitle);
}