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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_KEY_DOWN 133 
#define  GLFW_KEY_ESCAPE 132 
#define  GLFW_KEY_LEFT 131 
#define  GLFW_KEY_RIGHT 130 
#define  GLFW_KEY_UP 129 
#define  GLFW_KEY_Z 128 
 int GLFW_MOD_SHIFT ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double view_rotx ; 
 double view_roty ; 
 double view_rotz ; 

void key( GLFWwindow* window, int k, int s, int action, int mods )
{
  if( action != GLFW_PRESS ) return;

  switch (k) {
  case GLFW_KEY_Z:
    if( mods & GLFW_MOD_SHIFT )
      view_rotz -= 5.0;
    else
      view_rotz += 5.0;
    break;
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    break;
  case GLFW_KEY_UP:
    view_rotx += 5.0;
    break;
  case GLFW_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLFW_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLFW_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
}