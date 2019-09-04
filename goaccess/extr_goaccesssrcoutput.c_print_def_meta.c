#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ json_pretty_print; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fpskeysval (int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_def_meta (FILE * fp, const char *head, const char *desc, int sp)
{
  int isp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  fpskeysval (fp, "head", head, isp, 0);
  fpskeysval (fp, "desc", desc, isp, 0);
}