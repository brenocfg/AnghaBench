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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  LoadVar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lua_Number LoadNumber(LoadState* S)
{
 lua_Number x;
 LoadVar(S,x);
 return x;
}