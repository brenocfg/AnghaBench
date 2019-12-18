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
struct TYPE_4__ {unsigned int size; unsigned short* red; unsigned short* green; unsigned short* blue; } ;
typedef  int /*<<< orphan*/  GLFWmonitor ;
typedef  TYPE_1__ GLFWgammaramp ;

/* Variables and functions */
 float FLT_MAX ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,float) ; 
 float _glfw_fminf (float,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned short* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  free (unsigned short*) ; 
 TYPE_1__* glfwGetGammaRamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetGammaRamp (int /*<<< orphan*/ *,TYPE_1__*) ; 
 float powf (float,float) ; 

void glfwSetGamma(GLFWmonitor* handle, float gamma)
{
    unsigned int i;
    unsigned short* values;
    GLFWgammaramp ramp;
    const GLFWgammaramp* original;
    assert(handle != NULL);
    assert(gamma > 0.f);
    assert(gamma <= FLT_MAX);

    _GLFW_REQUIRE_INIT();

    if (gamma != gamma || gamma <= 0.f || gamma > FLT_MAX)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid gamma value %f", gamma);
        return;
    }

    original = glfwGetGammaRamp(handle);
    if (!original)
        return;

    values = calloc(original->size, sizeof(unsigned short));

    for (i = 0;  i < original->size;  i++)
    {
        float value;

        // Calculate intensity
        value = i / (float) (original->size - 1);
        // Apply gamma curve
        value = powf(value, 1.f / gamma) * 65535.f + 0.5f;
        // Clamp to value range
        value = _glfw_fminf(value, 65535.f);

        values[i] = (unsigned short) value;
    }

    ramp.red = values;
    ramp.green = values;
    ramp.blue = values;
    ramp.size = original->size;

    glfwSetGammaRamp(handle, &ramp);
    free(values);
}