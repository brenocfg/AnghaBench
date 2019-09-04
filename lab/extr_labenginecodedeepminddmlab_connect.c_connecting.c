#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_server; } ;
typedef  TYPE_1__ GameContext ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 int /*<<< orphan*/  Com_Frame () ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IN_Frame () ; 
 TYPE_3__ clc ; 

__attribute__((used)) static int connecting(GameContext* gc) {
  int err = !gc->is_server && clc.state < CA_ACTIVE ? EAGAIN : 0;
  IN_Frame();
  Com_Frame();
  return err;
}