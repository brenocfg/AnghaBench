#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  module; } ;
struct TYPE_5__ {scalar_t__ protocol; scalar_t__ method; } ;
typedef  TYPE_1__ GOutput ;
typedef  TYPE_2__ GHTML ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* output_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_def_avgts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_bw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_cumts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_def_hits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_maxts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_method (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_protocol (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_visitors (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_metrics (FILE * fp, const GHTML * def, int sp)
{
  const GOutput *output = output_lookup (def->module);

  print_def_hits (fp, sp);
  print_def_visitors (fp, sp);
  print_def_bw (fp, sp);
  print_def_avgts (fp, sp);
  print_def_cumts (fp, sp);
  print_def_maxts (fp, sp);

  if (output->method)
    print_def_method (fp, sp);
  if (output->protocol)
    print_def_protocol (fp, sp);

  print_def_data (fp, def->module, sp);
}