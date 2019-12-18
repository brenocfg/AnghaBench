#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  info; int /*<<< orphan*/  nval; } ;
struct TYPE_14__ {int k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
struct TYPE_15__ {int /*<<< orphan*/  nk; } ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  MAXINDEXRK ; 
 int RKASK (int /*<<< orphan*/ ) ; 
#define  VFALSE 132 
#define  VK 131 
#define  VKNUM 130 
#define  VNIL 129 
#define  VTRUE 128 
 int /*<<< orphan*/  boolK (TYPE_3__*,int) ; 
 int luaK_exp2anyreg (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2val (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_numberK (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilK (TYPE_3__*) ; 

int luaK_exp2RK (FuncState *fs, expdesc *e) {
  luaK_exp2val(fs, e);
  switch (e->k) {
    case VTRUE:
    case VFALSE:
    case VNIL: {
      if (fs->nk <= MAXINDEXRK) {  /* constant fits in RK operand? */
        e->u.info = (e->k == VNIL) ? nilK(fs) : boolK(fs, (e->k == VTRUE));
        e->k = VK;
        return RKASK(e->u.info);
      }
      else break;
    }
    case VKNUM: {
      e->u.info = luaK_numberK(fs, e->u.nval);
      e->k = VK;
      /* go through */
    }
    case VK: {
      if (e->u.info <= MAXINDEXRK)  /* constant fits in argC? */
        return RKASK(e->u.info);
      else break;
    }
    default: break;
  }
  /* not a constant in the right range: put it in a register */
  return luaK_exp2anyreg(fs, e);
}