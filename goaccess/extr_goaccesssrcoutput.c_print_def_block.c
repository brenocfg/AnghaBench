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
typedef  int /*<<< orphan*/  GDefMetric ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fpopen_obj (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_metric (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void
print_def_block (FILE * fp, const GDefMetric def, int sp, int last)
{
  fpopen_obj (fp, sp);
  print_def_metric (fp, def, sp);
  fpclose_obj (fp, sp, last);
}