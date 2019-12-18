#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int user; scalar_t__ nice; scalar_t__ irq; scalar_t__ idle; scalar_t__ sys; } ;
struct TYPE_11__ {int speed; TYPE_3__ cpu_times; void* model; } ;
typedef  TYPE_4__ uv_cpu_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  si11v1cpcmodel; } ;
struct TYPE_8__ {scalar_t__ si22v1cpucapability; } ;
struct TYPE_12__ {TYPE_2__ siv1v2si11v1; TYPE_1__ siv1v2si22v1; } ;
typedef  TYPE_5__ siv1v2 ;
typedef  void* data_area_ptr_assign_type ;
struct TYPE_13__ {scalar_t__ deref; void* assign; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ data_area_ptr ;

/* Variables and functions */
 int CPCMODEL_LENGTH ; 
 scalar_t__ CSD_NUMBER_ONLINE_CPUS ; 
 scalar_t__ CSD_OFFSET ; 
 scalar_t__ CVTOPCTP_OFFSET ; 
 scalar_t__ CVT_PTR ; 
 scalar_t__ RCTLACS_OFFSET ; 
 scalar_t__ RMCTRCT_OFFSET ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 void* uv__malloc (int) ; 

int uv_cpu_info(uv_cpu_info_t** cpu_infos, int* count) {
  uv_cpu_info_t* cpu_info;
  int idx;
  siv1v2 info;
  data_area_ptr cvt = {0};
  data_area_ptr csd = {0};
  data_area_ptr rmctrct = {0};
  data_area_ptr cvtopctp = {0};
  int cpu_usage_avg;

  cvt.assign = *(data_area_ptr_assign_type*)(CVT_PTR);

  csd.assign = *((data_area_ptr_assign_type *) (cvt.deref + CSD_OFFSET));
  cvtopctp.assign = *((data_area_ptr_assign_type *) (cvt.deref + CVTOPCTP_OFFSET));
  rmctrct.assign = *((data_area_ptr_assign_type *) (cvtopctp.deref + RMCTRCT_OFFSET));

  *count = *((int*) (csd.deref + CSD_NUMBER_ONLINE_CPUS));
  cpu_usage_avg = *((unsigned short int*) (rmctrct.deref + RCTLACS_OFFSET));

  *cpu_infos = uv__malloc(*count * sizeof(uv_cpu_info_t));
  if (!*cpu_infos)
    return UV_ENOMEM;

  cpu_info = *cpu_infos;
  idx = 0;
  while (idx < *count) {
    cpu_info->speed = *(int*)(info.siv1v2si22v1.si22v1cpucapability);
    cpu_info->model = uv__malloc(CPCMODEL_LENGTH + 1);
    memset(cpu_info->model, '\0', CPCMODEL_LENGTH + 1);
    memcpy(cpu_info->model, info.siv1v2si11v1.si11v1cpcmodel, CPCMODEL_LENGTH);
    cpu_info->cpu_times.user = cpu_usage_avg;
    /* TODO: implement the following */
    cpu_info->cpu_times.sys = 0;
    cpu_info->cpu_times.idle = 0;
    cpu_info->cpu_times.irq = 0;
    cpu_info->cpu_times.nice = 0;
    ++cpu_info;
    ++idx;
  }

  return 0;
}