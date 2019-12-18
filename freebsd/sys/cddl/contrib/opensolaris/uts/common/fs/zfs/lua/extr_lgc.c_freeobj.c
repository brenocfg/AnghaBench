#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  nuse; } ;
struct TYPE_10__ {TYPE_1__ strt; } ;
struct TYPE_9__ {int tt; } ;
struct TYPE_8__ {int /*<<< orphan*/  nupvalues; } ;
struct TYPE_7__ {int /*<<< orphan*/  nupvalues; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_5__* G (int /*<<< orphan*/ *) ; 
#define  LUA_TCCL 136 
#define  LUA_TLCL 135 
#define  LUA_TLNGSTR 134 
#define  LUA_TPROTO 133 
#define  LUA_TSHRSTR 132 
#define  LUA_TTABLE 131 
#define  LUA_TTHREAD 130 
#define  LUA_TUPVAL 129 
#define  LUA_TUSERDATA 128 
 TYPE_4__* gch (int /*<<< orphan*/ *) ; 
 TYPE_3__* gco2ccl (int /*<<< orphan*/ *) ; 
 TYPE_2__* gco2lcl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2t (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2th (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2ts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2uv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaE_freethread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeupval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_freemem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeCclosure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeLclosure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeudata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeobj (lua_State *L, GCObject *o) {
  switch (gch(o)->tt) {
    case LUA_TPROTO: luaF_freeproto(L, gco2p(o)); break;
    case LUA_TLCL: {
      luaM_freemem(L, o, sizeLclosure(gco2lcl(o)->nupvalues));
      break;
    }
    case LUA_TCCL: {
      luaM_freemem(L, o, sizeCclosure(gco2ccl(o)->nupvalues));
      break;
    }
    case LUA_TUPVAL: luaF_freeupval(L, gco2uv(o)); break;
    case LUA_TTABLE: luaH_free(L, gco2t(o)); break;
    case LUA_TTHREAD: luaE_freethread(L, gco2th(o)); break;
    case LUA_TUSERDATA: luaM_freemem(L, o, sizeudata(gco2u(o))); break;
    case LUA_TSHRSTR:
      G(L)->strt.nuse--;
      /* FALLTHROUGH */
    case LUA_TLNGSTR: {
      luaM_freemem(L, o, sizestring(gco2ts(o)));
      break;
    }
    default: lua_assert(0);
  }
}