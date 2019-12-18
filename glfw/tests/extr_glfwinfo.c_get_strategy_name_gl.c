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
typedef  scalar_t__ GLint ;

/* Variables and functions */
 scalar_t__ GL_LOSE_CONTEXT_ON_RESET_ARB ; 
 scalar_t__ GL_NO_RESET_NOTIFICATION_ARB ; 
 char const* STRATEGY_NAME_LOSE ; 
 char const* STRATEGY_NAME_NONE ; 

__attribute__((used)) static const char* get_strategy_name_gl(GLint strategy)
{
    if (strategy == GL_LOSE_CONTEXT_ON_RESET_ARB)
        return STRATEGY_NAME_LOSE;
    if (strategy == GL_NO_RESET_NOTIFICATION_ARB)
        return STRATEGY_NAME_NONE;

    return "unknown";
}