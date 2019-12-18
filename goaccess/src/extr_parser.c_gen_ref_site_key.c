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
struct TYPE_3__ {char* site; } ;
typedef  TYPE_1__ GLogItem ;
typedef  int /*<<< orphan*/  GKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  get_kdata (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
gen_ref_site_key (GKeyData * kdata, GLogItem * logitem)
{
  if (logitem->site[0] == '\0')
    return 1;

  get_kdata (kdata, logitem->site, logitem->site);

  return 0;
}