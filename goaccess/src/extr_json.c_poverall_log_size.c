#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  OVERALL_LOGSIZE ; 
 int /*<<< orphan*/  TAB ; 
 scalar_t__ get_log_sizes () ; 
 int /*<<< orphan*/  nlines ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poverall_log_size (GJSON * json, int sp)
{
  pjson (json, "%.*s\"%s\": %jd,%.*s", sp, TAB, OVERALL_LOGSIZE,
         (intmax_t) get_log_sizes (), nlines, NL);
}