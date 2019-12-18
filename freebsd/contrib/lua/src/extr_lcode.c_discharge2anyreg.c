#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ k; } ;
typedef  TYPE_1__ expdesc ;
struct TYPE_9__ {scalar_t__ freereg; } ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 scalar_t__ VNONRELOC ; 
 int /*<<< orphan*/  discharge2reg (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  luaK_reserveregs (TYPE_2__*,int) ; 

__attribute__((used)) static void discharge2anyreg (FuncState *fs, expdesc *e) {
  if (e->k != VNONRELOC) {  /* no fixed register yet? */
    luaK_reserveregs(fs, 1);  /* get a register */
    discharge2reg(fs, e, fs->freereg-1);  /* put value there */
  }
}