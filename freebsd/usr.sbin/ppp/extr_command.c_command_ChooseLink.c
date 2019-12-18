#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct link {int dummy; } ;
struct datalink {TYPE_1__* physical; } ;
struct cmdargs {TYPE_7__* bundle; TYPE_3__* cx; } ;
struct TYPE_11__ {int /*<<< orphan*/  mrru; } ;
struct TYPE_12__ {struct link link; TYPE_4__ cfg; } ;
struct TYPE_13__ {TYPE_5__ mp; } ;
struct TYPE_14__ {TYPE_6__ ncp; } ;
struct TYPE_10__ {TYPE_2__* physical; } ;
struct TYPE_9__ {struct link link; } ;
struct TYPE_8__ {struct link link; } ;

/* Variables and functions */
 struct datalink* bundle2datalink (TYPE_7__*,int /*<<< orphan*/ *) ; 

struct link *
command_ChooseLink(struct cmdargs const *arg)
{
  if (arg->cx)
    return &arg->cx->physical->link;
  else if (!arg->bundle->ncp.mp.cfg.mrru) {
    struct datalink *dl = bundle2datalink(arg->bundle, NULL);
    if (dl)
      return &dl->physical->link;
  }
  return &arg->bundle->ncp.mp.link;
}