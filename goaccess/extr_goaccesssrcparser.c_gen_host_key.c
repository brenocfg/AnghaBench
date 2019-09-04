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
struct TYPE_3__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ GLogItem ;
typedef  int /*<<< orphan*/  GKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  get_kdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gen_host_key (GKeyData * kdata, GLogItem * logitem)
{
  if (!logitem->host)
    return 1;

  get_kdata (kdata, logitem->host, logitem->host);

  return 0;
}