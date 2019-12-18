#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* func_setInt32 ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (TYPE_1__*,char const*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

void SDL_AMediaFormat_setInt32(SDL_AMediaFormat* aformat, const char* name, int32_t value)
{
    assert(aformat->func_setInt32);
    aformat->func_setInt32(aformat, name, value);
}