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
struct TYPE_4__ {scalar_t__ is_static; scalar_t__ is_404; int /*<<< orphan*/  req; } ;
typedef  TYPE_1__ GLogItem ;
typedef  int /*<<< orphan*/  GKeyData ;

/* Variables and functions */
 int gen_req_key (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
gen_request_key (GKeyData * kdata, GLogItem * logitem)
{
  if (!logitem->req || logitem->is_404 || logitem->is_static)
    return 1;

  return gen_req_key (kdata, logitem);
}