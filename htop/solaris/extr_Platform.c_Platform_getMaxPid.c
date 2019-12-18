#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int v_proc; } ;
typedef  TYPE_1__ kvar_t ;
struct TYPE_6__ {TYPE_1__* ks_data; } ;
typedef  TYPE_2__ kstat_t ;
typedef  int /*<<< orphan*/  kstat_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  kstat_close (int /*<<< orphan*/ *) ; 
 TYPE_2__* kstat_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * kstat_open () ; 
 int /*<<< orphan*/  kstat_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

int Platform_getMaxPid() {
   kstat_ctl_t *kc = NULL;
   kstat_t *kshandle = NULL;
   kvar_t *ksvar = NULL;
   int vproc = 32778; // Reasonable Solaris default
   kc = kstat_open();
   if (kc != NULL) { kshandle = kstat_lookup(kc,"unix",0,"var"); }
   if (kshandle != NULL) { kstat_read(kc,kshandle,NULL); }
   ksvar = kshandle->ks_data;
   if (ksvar->v_proc > 0 ) {
      vproc = ksvar->v_proc;
   }
   if (kc != NULL) { kstat_close(kc); }
   return vproc; 
}