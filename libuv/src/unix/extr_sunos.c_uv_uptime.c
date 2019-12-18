#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kstat_t ;
struct TYPE_3__ {long ul; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
typedef  TYPE_2__ kstat_named_t ;
typedef  int /*<<< orphan*/  kstat_ctl_t ;

/* Variables and functions */
 int UV_EPERM ; 
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 int /*<<< orphan*/  kstat_close (int /*<<< orphan*/ *) ; 
 scalar_t__ kstat_data_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * kstat_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * kstat_open () ; 
 int kstat_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

int uv_uptime(double* uptime) {
  kstat_ctl_t   *kc;
  kstat_t       *ksp;
  kstat_named_t *knp;

  long hz = sysconf(_SC_CLK_TCK);

  kc = kstat_open();
  if (kc == NULL)
    return UV_EPERM;

  ksp = kstat_lookup(kc, (char*) "unix", 0, (char*) "system_misc");
  if (kstat_read(kc, ksp, NULL) == -1) {
    *uptime = -1;
  } else {
    knp = (kstat_named_t*)  kstat_data_lookup(ksp, (char*) "clk_intr");
    *uptime = knp->value.ul / hz;
  }
  kstat_close(kc);

  return 0;
}