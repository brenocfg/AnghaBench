#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_4__ {int modifiers; int /*<<< orphan*/  keymap; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ xkb; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int const GLFW_MOD_ALT ; 
 int const GLFW_MOD_CONTROL ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputChar (int /*<<< orphan*/ *,long,int const,int const) ; 
 long _glfwKeySym2Unicode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  composeSymbol (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xkb_keymap_key_repeats (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int xkb_state_key_get_syms (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static GLFWbool inputChar(_GLFWwindow* window, uint32_t key)
{
    uint32_t code, numSyms;
    long cp;
    const xkb_keysym_t *syms;
    xkb_keysym_t sym;

    code = key + 8;
    numSyms = xkb_state_key_get_syms(_glfw.wl.xkb.state, code, &syms);

    if (numSyms == 1)
    {
#ifdef HAVE_XKBCOMMON_COMPOSE_H
        sym = composeSymbol(syms[0]);
#else
        sym = syms[0];
#endif
        cp = _glfwKeySym2Unicode(sym);
        if (cp != -1)
        {
            const int mods = _glfw.wl.xkb.modifiers;
            const int plain = !(mods & (GLFW_MOD_CONTROL | GLFW_MOD_ALT));
            _glfwInputChar(window, cp, mods, plain);
        }
    }

    return xkb_keymap_key_repeats(_glfw.wl.xkb.keymap, syms[0]);
}