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
struct TYPE_3__ {scalar_t__ status; scalar_t__ (* writer ) (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  L; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DumpBlock(const void* b, size_t size, DumpState* D)
{
 if (D->status==0)
 {
  lua_unlock(D->L);
  D->status=(*D->writer)(D->L,b,size,D->data);
  lua_lock(D->L);
 }
}