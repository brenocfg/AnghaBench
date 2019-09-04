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
struct TYPE_5__ {scalar_t__ nice; scalar_t__ irq; scalar_t__ idle; scalar_t__ sys; scalar_t__ user; } ;
struct TYPE_6__ {TYPE_1__ cpu_times; int /*<<< orphan*/  model; scalar_t__ speed; } ;
typedef  TYPE_2__ uv_cpu_info_t ;

/* Variables and functions */
 int UV_ENOMEM ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 unsigned int sysconf (int /*<<< orphan*/ ) ; 
 TYPE_2__* uv__malloc (unsigned int) ; 
 int /*<<< orphan*/  uv__strdup (char*) ; 

int uv_cpu_info(uv_cpu_info_t** cpu_infos, int* count) {
  unsigned int numcpus, idx = 0;
  uv_cpu_info_t* cpu_info;

  *cpu_infos = NULL;
  *count = 0;

  numcpus = sysconf(_SC_NPROCESSORS_ONLN);

  *cpu_infos = uv__malloc(numcpus * sizeof(uv_cpu_info_t));
  if (!*cpu_infos) {
    return UV_ENOMEM;
  }

  cpu_info = *cpu_infos;
  for (idx = 0; idx < numcpus; idx++) {
    cpu_info->speed = 0;
    cpu_info->model = uv__strdup("unknown");
    cpu_info->cpu_times.user = 0;
    cpu_info->cpu_times.sys = 0;
    cpu_info->cpu_times.idle = 0;
    cpu_info->cpu_times.irq = 0;
    cpu_info->cpu_times.nice = 0;
    cpu_info++;
  }
  *count = numcpus;

  return 0;
}