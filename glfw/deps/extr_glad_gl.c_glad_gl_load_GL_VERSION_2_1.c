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
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X3FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X2FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X4FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X2FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X4FVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X3FVPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_2_1 ; 
 scalar_t__ glUniformMatrix2x3fv ; 
 scalar_t__ glUniformMatrix2x4fv ; 
 scalar_t__ glUniformMatrix3x2fv ; 
 scalar_t__ glUniformMatrix3x4fv ; 
 scalar_t__ glUniformMatrix4x2fv ; 
 scalar_t__ glUniformMatrix4x3fv ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_2_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_2_1) return;
    glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) load("glUniformMatrix2x3fv", userptr);
    glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) load("glUniformMatrix2x4fv", userptr);
    glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) load("glUniformMatrix3x2fv", userptr);
    glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) load("glUniformMatrix3x4fv", userptr);
    glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) load("glUniformMatrix4x2fv", userptr);
    glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) load("glUniformMatrix4x3fv", userptr);
}