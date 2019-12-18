#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  append_method; } ;
struct TYPE_4__ {char* datakey; char* datatype; char* cwidth; int /*<<< orphan*/  lbl; } ;
typedef  TYPE_1__ GDefMetric ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_METHODS_LBL ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  print_def_block (int /*<<< orphan*/ *,TYPE_1__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_def_method (FILE * fp, int sp)
{
  GDefMetric def = {
    .datakey = "method",
    .lbl = MTRC_METHODS_LBL,
    .datatype = "string",
    .cwidth = "6%",
  };

  if (!conf.append_method)
    return;

  print_def_block (fp, def, sp, 0);
}