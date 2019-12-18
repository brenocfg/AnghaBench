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
struct TYPE_2__ {char** filenames; int filenames_idx; } ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  TAB ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  escape_json_output (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
poverall_log_path (GJSON * json, int idx, int isp)
{
  pjson (json, "%.*s\"", isp, TAB);
  if (conf.filenames[idx][0] == '-' && conf.filenames[idx][1] == '\0')
    pjson (json, "STDIN");
  else
    escape_json_output (json, (char *) conf.filenames[idx]);
  pjson (json, conf.filenames_idx - 1 != idx ? "\",\n" : "\"");
}