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

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 float angle ; 
 int /*<<< orphan*/  gear1 ; 
 int /*<<< orphan*/  gear2 ; 
 int /*<<< orphan*/  gear3 ; 
 int /*<<< orphan*/  glCallList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glRotatef (float,float,float,float) ; 
 int /*<<< orphan*/  glTranslatef (float,float,float) ; 
 float view_rotx ; 
 float view_roty ; 
 float view_rotz ; 

__attribute__((used)) static void draw(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    glRotatef(view_rotz, 0.0, 0.0, 1.0);

    glPushMatrix();
      glTranslatef(-3.0, -2.0, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glCallList(gear1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(3.1f, -2.f, 0.f);
      glRotatef(-2.f * angle - 9.f, 0.f, 0.f, 1.f);
      glCallList(gear2);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-3.1f, 4.2f, 0.f);
      glRotatef(-2.f * angle - 25.f, 0.f, 0.f, 1.f);
      glCallList(gear3);
    glPopMatrix();

  glPopMatrix();
}