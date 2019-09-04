#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 int /*<<< orphan*/  SPEC_TOKN_NUL ; 
 int /*<<< orphan*/  SPEC_TOKN_SET ; 
 int /*<<< orphan*/  find_xff_host (TYPE_1__*,char**,char**) ; 
 int spec_err (TYPE_1__*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
special_specifier (GLogItem * logitem, char **str, char **p)
{
  switch (**p) {
    /* XFF remote hostname (IP only) */
  case 'h':
    if (logitem->host)
      return spec_err (logitem, SPEC_TOKN_SET, **p, NULL);
    if (find_xff_host (logitem, str, p))
      return spec_err (logitem, SPEC_TOKN_NUL, 'h', NULL);
    break;
  }

  return 0;
}