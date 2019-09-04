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
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 scalar_t__ GL_INVALID_INDEX ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ glGetUniformBlockIndex (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* programs ; 

__attribute__((used)) static inline GLuint
block_index(int program, const char *name) {
    GLuint ans = glGetUniformBlockIndex(programs[program].id, name);
    if (ans == GL_INVALID_INDEX) { fatal("Could not find block index"); }
    return ans;
}