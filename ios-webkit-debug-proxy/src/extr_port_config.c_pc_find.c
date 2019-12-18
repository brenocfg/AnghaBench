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
typedef  TYPE_1__* pc_t ;
typedef  TYPE_2__* pc_entry_t ;
struct TYPE_6__ {char* device_id; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

const pc_entry_t pc_find(pc_t self, const char *device_id) {
  pc_entry_t e;
  for (e = self->head; e; e = e->next) {
    const char *s = e->device_id;
    if ((s && !strcmp(s, "*")) ||
        (device_id ? (s && !strcasecmp(s, device_id)) : !s)) {
      return e;
    }
  }
  return NULL;
}