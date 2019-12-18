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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {scalar_t__ json_pretty_print; int /*<<< orphan*/  bandwidth; } ;
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  ht_get_bw_min_max (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_get_meta_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
pmeta_data_bw (GJSON * json, GModule module, int sp)
{
  int isp = 0;
  uint64_t max = 0, min = 0;

  if (!conf.bandwidth)
    return;

  ht_get_bw_min_max (module, &min, &max);

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  popen_obj_attr (json, "bytes", sp);
  pskeyu64val (json, "count", ht_get_meta_data (module, "bytes"), isp, 0);
  pskeyu64val (json, "max", max, isp, 0);
  pskeyu64val (json, "min", min, isp, 1);
  pclose_obj (json, sp, 0);
}