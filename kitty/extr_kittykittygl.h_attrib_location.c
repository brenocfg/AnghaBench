#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* programs ; 

__attribute__((used)) static inline GLint
attrib_location(int program, const char *name) {
    GLint ans = glGetAttribLocation(programs[program].id, name);
    return ans;
}