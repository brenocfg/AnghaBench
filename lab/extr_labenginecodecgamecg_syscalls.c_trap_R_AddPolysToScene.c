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
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  polyVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_R_ADDPOLYSTOSCENE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 

void	trap_R_AddPolysToScene( qhandle_t hShader , int numVerts, const polyVert_t *verts, int num ) {
	syscall( CG_R_ADDPOLYSTOSCENE, hShader, numVerts, verts, num );
}