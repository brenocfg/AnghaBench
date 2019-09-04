#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ height; scalar_t__ width; scalar_t__ buffer; int /*<<< orphan*/ * handle; } ;
struct TYPE_6__ {TYPE_1__ osmesa; } ;
struct TYPE_7__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  OSMesaDestroyContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void destroyContextOSMesa(_GLFWwindow* window)
{
    if (window->context.osmesa.handle)
    {
        OSMesaDestroyContext(window->context.osmesa.handle);
        window->context.osmesa.handle = NULL;
    }

    if (window->context.osmesa.buffer)
    {
        free(window->context.osmesa.buffer);
        window->context.osmesa.width = 0;
        window->context.osmesa.height = 0;
    }
}