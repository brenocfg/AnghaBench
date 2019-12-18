#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nupvalues; int /*<<< orphan*/ * v; int /*<<< orphan*/ * upvalue; } ;
struct TYPE_10__ {TYPE_4__** upvals; TYPE_2__* p; } ;
struct TYPE_9__ {int sizeupvalues; TYPE_1__* upvalues; } ;
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_2__ Proto ;
typedef  TYPE_3__ LClosure ;
typedef  int /*<<< orphan*/  GCObject ;
typedef  TYPE_4__ CClosure ;

/* Variables and functions */
#define  LUA_TCCL 129 
#define  LUA_TLCL 128 
 TYPE_4__* clCvalue (int /*<<< orphan*/ ) ; 
 TYPE_3__* clLvalue (int /*<<< orphan*/ ) ; 
 char const* getstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_4__*) ; 
 int ttype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *aux_upvalue (StkId fi, int n, TValue **val,
                                GCObject **owner) {
  switch (ttype(fi)) {
    case LUA_TCCL: {  /* C closure */
      CClosure *f = clCvalue(fi);
      if (!(1 <= n && n <= f->nupvalues)) return NULL;
      *val = &f->upvalue[n-1];
      if (owner) *owner = obj2gco(f);
      return "";
    }
    case LUA_TLCL: {  /* Lua closure */
      LClosure *f = clLvalue(fi);
      TString *name;
      Proto *p = f->p;
      if (!(1 <= n && n <= p->sizeupvalues)) return NULL;
      *val = f->upvals[n-1]->v;
      if (owner) *owner = obj2gco(f->upvals[n - 1]);
      name = p->upvalues[n-1].name;
      return (name == NULL) ? "" : getstr(name);
    }
    default: return NULL;  /* not a closure */
  }
}