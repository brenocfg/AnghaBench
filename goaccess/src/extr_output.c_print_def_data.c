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
struct TYPE_3__ {char* cname; char* cwidth; char* datakey; char* datatype; char* metakey; char* metalbl; char* metatype; int /*<<< orphan*/  lbl; } ;
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_1__ GDefMetric ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_DATA_LBL ; 
 int /*<<< orphan*/  VISITORS ; 
 int /*<<< orphan*/  print_def_block (int /*<<< orphan*/ *,TYPE_1__,int,int) ; 

__attribute__((used)) static void
print_def_data (FILE * fp, GModule module, int sp)
{
  GDefMetric def = {
    .cname = "trunc",
    .cwidth = "100%",
    .datakey = "data",
    .datatype = module == VISITORS ? "date" : "string",
    .lbl = MTRC_DATA_LBL,
    .metakey = "unique",
    .metalbl = "Total",
    .metatype = "numeric",
  };

  print_def_block (fp, def, sp, 1);
}