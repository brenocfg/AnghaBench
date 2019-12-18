#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int speed; int /*<<< orphan*/  model; } ;
typedef  TYPE_3__ uv_cpu_info_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_15__ {int cpu_count; } ;
typedef  TYPE_4__ system_info ;
typedef  scalar_t__ status_t ;
struct TYPE_12__ {int default_frequency; } ;
struct TYPE_13__ {TYPE_1__ core; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__ data; } ;
typedef  TYPE_5__ cpu_topology_node_info ;

/* Variables and functions */
 scalar_t__ B_OK ; 
 scalar_t__ B_TOPOLOGY_CORE ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ get_cpu_topology_info (TYPE_5__*,int*) ; 
 scalar_t__ get_system_info (TYPE_4__*) ; 
 TYPE_3__* uv__calloc (int,int) ; 
 int /*<<< orphan*/  uv__free (TYPE_5__*) ; 
 TYPE_5__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv__strdup (char*) ; 

int uv_cpu_info(uv_cpu_info_t** cpu_infos, int* count) {
  cpu_topology_node_info* topology_infos;
  int i;
  status_t status;
  system_info system;
  uint32_t topology_count;
  uint64_t cpuspeed;
  uv_cpu_info_t* cpu_info;

  if (cpu_infos == NULL || count == NULL)
    return UV_EINVAL;

  status = get_cpu_topology_info(NULL, &topology_count);
  if (status != B_OK)
    return UV__ERR(status);

  topology_infos = uv__malloc(topology_count * sizeof(*topology_infos));
  if (topology_infos == NULL)
    return UV_ENOMEM;

  status = get_cpu_topology_info(topology_infos, &topology_count);
  if (status != B_OK) {
    uv__free(topology_infos);
    return UV__ERR(status);
  }

  cpuspeed = 0;
  for (i = 0; i < (int)topology_count; i++) {
    if (topology_infos[i].type == B_TOPOLOGY_CORE) {
      cpuspeed = topology_infos[i].data.core.default_frequency;
      break;
    }
  }

  uv__free(topology_infos);

  status = get_system_info(&system);
  if (status != B_OK)
    return UV__ERR(status);

  *cpu_infos = uv__calloc(system.cpu_count, sizeof(**cpu_infos));
  if (*cpu_infos == NULL)
    return UV_ENOMEM;

  /* CPU time and model are not exposed by Haiku. */
  cpu_info = *cpu_infos;
  for (i = 0; i < (int)system.cpu_count; i++) {
    cpu_info->model = uv__strdup("unknown");
    cpu_info->speed = (int)(cpuspeed / 1000000);
    cpu_info++;
  }
  *count = system.cpu_count;

  return 0;
}