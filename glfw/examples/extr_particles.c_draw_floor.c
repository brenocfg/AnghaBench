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
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_AND_EXECUTE ; 
 int /*<<< orphan*/  GL_DIFFUSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_SHININESS ; 
 int /*<<< orphan*/  GL_SPECULAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  floor_diffuse ; 
 int /*<<< orphan*/  floor_shininess ; 
 int /*<<< orphan*/  floor_specular ; 
 int /*<<< orphan*/  floor_tex_id ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCallList (scalar_t__) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glEndList () ; 
 scalar_t__ glGenLists (int) ; 
 int /*<<< orphan*/  glMaterialf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMaterialfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glNewList (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glNormal3f (float,float,float) ; 
 int /*<<< orphan*/  tessellate_floor (float,float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireframe ; 

__attribute__((used)) static void draw_floor(void)
{
    static GLuint floor_list = 0;

    if (!wireframe)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, floor_tex_id);
    }

    // The first time, we build the floor display list
    if (!floor_list)
    {
        floor_list = glGenLists(1);
        glNewList(floor_list, GL_COMPILE_AND_EXECUTE);

        glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, floor_shininess);

        // Draw floor as a bunch of triangle strips (high tessellation
        // improves lighting)
        glNormal3f(0.f, 0.f, 1.f);
        glBegin(GL_QUADS);
        tessellate_floor(-1.f, -1.f, 0.f, 0.f, 0);
        tessellate_floor( 0.f, -1.f, 1.f, 0.f, 0);
        tessellate_floor( 0.f,  0.f, 1.f, 1.f, 0);
        tessellate_floor(-1.f,  0.f, 0.f, 1.f, 0);
        glEnd();

        glEndList();
    }
    else
        glCallList(floor_list);

    glDisable(GL_TEXTURE_2D);

}