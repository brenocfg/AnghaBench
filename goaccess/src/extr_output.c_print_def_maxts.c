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
struct TYPE_5__ {int /*<<< orphan*/  serve_usecs; } ;
struct TYPE_4__ {char* datakey; char* datatype; char* metakey; char* cwidth; int /*<<< orphan*/  lbl; } ;
typedef  TYPE_1__ GDefMetric ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_MAXTS_LBL ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  print_def_block (int /*<<< orphan*/ *,TYPE_1__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_def_maxts (FILE * fp, int sp)
{
  GDefMetric def = {
    .datakey = "maxts",
    .lbl = MTRC_MAXTS_LBL,
    .datatype = "utime",
    .metakey = "count",
    .cwidth = "8%",
  };

  if (!conf.serve_usecs)
    return;
  print_def_block (fp, def, sp, 0);
}