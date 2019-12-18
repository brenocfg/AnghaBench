#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sizek; int sizep; int /*<<< orphan*/ * p; int /*<<< orphan*/ * k; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpChar (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  LUA_TBOOLEAN 131 
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/  const*) ; 
 int ttypenv (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void DumpConstants(const Proto* f, DumpState* D)
{
 int i,n=f->sizek;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  const TValue* o=&f->k[i];
  DumpChar(ttypenv(o),D);
  switch (ttypenv(o))
  {
   case LUA_TNIL:
	break;
   case LUA_TBOOLEAN:
	DumpChar(bvalue(o),D);
	break;
   case LUA_TNUMBER:
	DumpNumber(nvalue(o),D);
	break;
   case LUA_TSTRING:
	DumpString(rawtsvalue(o),D);
	break;
    default: lua_assert(0);
  }
 }
 n=f->sizep;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpFunction(f->p[i],D);
}