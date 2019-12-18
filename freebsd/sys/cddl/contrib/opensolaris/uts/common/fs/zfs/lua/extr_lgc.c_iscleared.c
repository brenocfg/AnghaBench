#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  iscollectable (int /*<<< orphan*/  const*) ; 
 int iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int iscleared (global_State *g, const TValue *o) {
  if (!iscollectable(o)) return 0;
  else if (ttisstring(o)) {
    markobject(g, rawtsvalue(o));  /* strings are `values', so are never weak */
    return 0;
  }
  else return iswhite(gcvalue(o));
}