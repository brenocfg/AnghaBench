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
struct TYPE_5__ {scalar_t__ json_pretty_print; } ;
struct TYPE_4__ {int /*<<< orphan*/  ht_size; int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 TYPE_3__ conf ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmeta_data_avgts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_bw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_cumts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_hits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_maxts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_unique (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmeta_data_visitors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
print_meta_data (GJSON * json, GHolder * h, int sp)
{
  int isp = 0, iisp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1, iisp = sp + 2;

  popen_obj_attr (json, "metadata", isp);

  pmeta_data_avgts (json, h->module, iisp);
  pmeta_data_cumts (json, h->module, iisp);
  pmeta_data_maxts (json, h->module, iisp);
  pmeta_data_bw (json, h->module, iisp);
  pmeta_data_visitors (json, h->module, iisp);
  pmeta_data_hits (json, h->module, iisp);
  pmeta_data_unique (json, h->ht_size, iisp);

  pclose_obj (json, isp, 0);
}