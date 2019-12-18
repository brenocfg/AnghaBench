#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_16__ {int /*<<< orphan*/  lnglen; } ;
struct TYPE_18__ {TYPE_1__ u; int /*<<< orphan*/  shrlen; } ;
struct TYPE_17__ {int tt; } ;
struct TYPE_15__ {int /*<<< orphan*/  nupvalues; } ;
typedef  TYPE_2__ GCObject ;

/* Variables and functions */
#define  LUA_TCCL 135 
#define  LUA_TLCL 134 
#define  LUA_TLNGSTR 133 
#define  LUA_TPROTO 132 
#define  LUA_TSHRSTR 131 
#define  LUA_TTABLE 130 
#define  LUA_TTHREAD 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  freeLclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_12__* gco2ccl (TYPE_2__*) ; 
 int /*<<< orphan*/  gco2lcl (TYPE_2__*) ; 
 int /*<<< orphan*/  gco2p (TYPE_2__*) ; 
 int /*<<< orphan*/  gco2t (TYPE_2__*) ; 
 int /*<<< orphan*/  gco2th (TYPE_2__*) ; 
 TYPE_3__* gco2ts (TYPE_2__*) ; 
 int /*<<< orphan*/  gco2u (TYPE_2__*) ; 
 int /*<<< orphan*/  luaE_freethread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_freemem (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeCclosure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizelstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeudata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeobj (lua_State *L, GCObject *o) {
  switch (o->tt) {
    case LUA_TPROTO: luaF_freeproto(L, gco2p(o)); break;
    case LUA_TLCL: {
      freeLclosure(L, gco2lcl(o));
      break;
    }
    case LUA_TCCL: {
      luaM_freemem(L, o, sizeCclosure(gco2ccl(o)->nupvalues));
      break;
    }
    case LUA_TTABLE: luaH_free(L, gco2t(o)); break;
    case LUA_TTHREAD: luaE_freethread(L, gco2th(o)); break;
    case LUA_TUSERDATA: luaM_freemem(L, o, sizeudata(gco2u(o))); break;
    case LUA_TSHRSTR:
      luaS_remove(L, gco2ts(o));  /* remove it from hash table */
      luaM_freemem(L, o, sizelstring(gco2ts(o)->shrlen));
      break;
    case LUA_TLNGSTR: {
      luaM_freemem(L, o, sizelstring(gco2ts(o)->u.lnglen));
      break;
    }
    default: lua_assert(0);
  }
}