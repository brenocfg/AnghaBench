#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int numVertexes; int /*<<< orphan*/ * normal; int /*<<< orphan*/ * xyz; } ;
typedef  TYPE_1__ shaderCommands_t ;
struct TYPE_5__ {int /*<<< orphan*/  whiteImage; } ;

/* Variables and functions */
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_POLYMODE_LINE ; 
 int /*<<< orphan*/  GL_Bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglColor3f (int,int,int) ; 
 int /*<<< orphan*/  qglDepthRange (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglVertex3fv (int /*<<< orphan*/ ) ; 
 TYPE_2__ tr ; 

__attribute__((used)) static void DrawNormals (shaderCommands_t *input) {
	int		i;
	vec3_t	temp;

	GL_Bind( tr.whiteImage );
	qglColor3f (1,1,1);
	qglDepthRange( 0, 0 );	// never occluded
	GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );

	qglBegin (GL_LINES);
	for (i = 0 ; i < input->numVertexes ; i++) {
		qglVertex3fv (input->xyz[i]);
		VectorMA (input->xyz[i], 2, input->normal[i], temp);
		qglVertex3fv (temp);
	}
	qglEnd ();

	qglDepthRange( 0, 1 );
}