#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ idx; } ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  OVERALL_ENDDATE ; 
 int /*<<< orphan*/  OVERALL_STARTDATE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_start_end_parsing_dates (TYPE_1__*,char**,char**,char*) ; 
 int /*<<< orphan*/  pskeysval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poverall_start_end_date (GJSON * json, GHolder * h, int sp)
{
  char *start = NULL, *end = NULL;

  if (h->idx == 0 || get_start_end_parsing_dates (h, &start, &end, "%d/%b/%Y"))
    return;

  pskeysval (json, OVERALL_STARTDATE, start, sp, 0);
  pskeysval (json, OVERALL_ENDDATE, end, sp, 0);

  free (end);
  free (start);
}