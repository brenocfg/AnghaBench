#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* func_setBuffer ) (TYPE_1__*,char const*,void*,size_t) ;int /*<<< orphan*/  func_setInt32; } ;
typedef  TYPE_1__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,void*,size_t) ; 

void SDL_AMediaFormat_setBuffer(SDL_AMediaFormat* aformat, const char* name, void* data, size_t size)
{
    assert(aformat->func_setInt32);
    aformat->func_setBuffer(aformat, name, data, size);
}