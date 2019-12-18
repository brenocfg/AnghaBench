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
typedef  int GLfloat ;

/* Variables and functions */
 float ANIMATION_SPEED ; 
 int /*<<< orphan*/  BounceBall (double) ; 
 double DIST_BALL ; 
 scalar_t__ DRAW_BALL_SHADOW ; 
 int /*<<< orphan*/  DrawBoingBallBand (int,scalar_t__) ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_NORMALIZE ; 
 double MAX_DELTA_T ; 
 double SHADOW_OFFSET_X ; 
 double SHADOW_OFFSET_Y ; 
 double SHADOW_OFFSET_Z ; 
 scalar_t__ STEP_LONGITUDE ; 
 float TruncateDeg (float) ; 
 double ball_x ; 
 double ball_y ; 
 float deg_rot_y ; 
 float deg_rot_y_inc ; 
 scalar_t__ drawBallHow ; 
 double dt ; 
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glRotatef (float,double,double,double) ; 
 int /*<<< orphan*/  glTranslatef (double,double,double) ; 

void DrawBoingBall( void )
{
   GLfloat lon_deg;     /* degree of longitude */
   double dt_total, dt2;

   glPushMatrix();
   glMatrixMode( GL_MODELVIEW );

  /*
   * Another relative Z translation to separate objects.
   */
   glTranslatef( 0.0, 0.0, DIST_BALL );

   /* Update ball position and rotation (iterate if necessary) */
   dt_total = dt;
   while( dt_total > 0.0 )
   {
       dt2 = dt_total > MAX_DELTA_T ? MAX_DELTA_T : dt_total;
       dt_total -= dt2;
       BounceBall( dt2 );
       deg_rot_y = TruncateDeg( deg_rot_y + deg_rot_y_inc*((float)dt2*ANIMATION_SPEED) );
   }

   /* Set ball position */
   glTranslatef( ball_x, ball_y, 0.0 );

  /*
   * Offset the shadow.
   */
   if ( drawBallHow == DRAW_BALL_SHADOW )
   {
      glTranslatef( SHADOW_OFFSET_X,
                    SHADOW_OFFSET_Y,
                    SHADOW_OFFSET_Z );
   }

  /*
   * Tilt the ball.
   */
   glRotatef( -20.0, 0.0, 0.0, 1.0 );

  /*
   * Continually rotate ball around Y axis.
   */
   glRotatef( deg_rot_y, 0.0, 1.0, 0.0 );

  /*
   * Set OpenGL state for Boing ball.
   */
   glCullFace( GL_FRONT );
   glEnable( GL_CULL_FACE );
   glEnable( GL_NORMALIZE );

  /*
   * Build a faceted latitude slice of the Boing ball,
   * stepping same-sized vertical bands of the sphere.
   */
   for ( lon_deg = 0;
         lon_deg < 180;
         lon_deg += STEP_LONGITUDE )
   {
     /*
      * Draw a latitude circle at this longitude.
      */
      DrawBoingBallBand( lon_deg,
                         lon_deg + STEP_LONGITUDE );
   }

   glPopMatrix();

   return;
}