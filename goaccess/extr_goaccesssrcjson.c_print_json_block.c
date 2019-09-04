#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  TAB ; 
 int /*<<< orphan*/  escape_json_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pavgts (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pbw (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pcumts (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  phits (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pmaxts (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pmethod (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pprotocol (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pvisitors (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
print_json_block (GJSON * json, GMetrics * nmetrics, int sp)
{
  /* print hits */
  phits (json, nmetrics, sp);
  /* print visitors */
  pvisitors (json, nmetrics, sp);
  /* print bandwidth */
  pbw (json, nmetrics, sp);

  /* print time served metrics */
  pavgts (json, nmetrics, sp);
  pcumts (json, nmetrics, sp);
  pmaxts (json, nmetrics, sp);

  /* print protocol/method */
  pmethod (json, nmetrics, sp);
  pprotocol (json, nmetrics, sp);

  /* data metric */
  pjson (json, "%.*s\"data\": \"", sp, TAB);
  escape_json_output (json, nmetrics->data);
  pjson (json, "\"");
}