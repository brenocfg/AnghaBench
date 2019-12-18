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
struct iwdp_ifs_struct {int dummy; } ;
typedef  TYPE_2__* iwdp_ifs_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_IFS ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

iwdp_ifs_t iwdp_ifs_new() {
  iwdp_ifs_t ifs = (iwdp_ifs_t)malloc(sizeof(struct iwdp_ifs_struct));
  if (ifs) {
    memset(ifs, 0, sizeof(struct iwdp_ifs_struct));
    ifs->type.type = TYPE_IFS;
  }
  return ifs;
}