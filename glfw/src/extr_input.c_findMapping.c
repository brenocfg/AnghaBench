#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ _GLFWmapping ;
struct TYPE_5__ {int mappingCount; TYPE_1__* mappings; } ;

/* Variables and functions */
 TYPE_3__ _glfw ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static _GLFWmapping* findMapping(const char* guid)
{
    int i;

    for (i = 0;  i < _glfw.mappingCount;  i++)
    {
        if (strcmp(_glfw.mappings[i].guid, guid) == 0)
            return _glfw.mappings + i;
    }

    return NULL;
}