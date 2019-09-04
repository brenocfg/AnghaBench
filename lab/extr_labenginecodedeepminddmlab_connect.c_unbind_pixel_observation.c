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
typedef  int /*<<< orphan*/  GameContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglUnmapBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ use_pbo_rendering (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unbind_pixel_observation(GameContext* gc) {
  if (use_pbo_rendering(gc)) {
    qglUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    qglBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
  }
}