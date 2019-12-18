#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;
typedef  scalar_t__ const Atom ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ const None ; 
 scalar_t__ XInternAtom (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ _glfw ; 

__attribute__((used)) static Atom getSupportedAtom(Atom* supportedAtoms,
                             unsigned long atomCount,
                             const char* atomName)
{
    const Atom atom = XInternAtom(_glfw.x11.display, atomName, False);

    for (unsigned int i = 0;  i < atomCount;  i++)
    {
        if (supportedAtoms[i] == atom)
            return atom;
    }

    return None;
}