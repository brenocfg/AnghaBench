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
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  ht_get_meta_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ht_get_visitors_min_max (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pskeyival (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmeta_data_visitors (GJSON * json, GModule module, int sp)
{
  int isp = 0;
  int max = 0, min = 0;

  ht_get_visitors_min_max (module, &min, &max);

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  popen_obj_attr (json, "visitors", sp);
  pskeyu64val (json, "count", ht_get_meta_data (module, "visitors"), isp, 0);
  pskeyival (json, "max", max, isp, 0);
  pskeyival (json, "min", min, isp, 1);
  pclose_obj (json, sp, 0);
}