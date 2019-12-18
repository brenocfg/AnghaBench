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
typedef  scalar_t__ PFNGLSAMPLECOVERAGEPROC ;
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXFPROC ;
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXDPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXFPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXDPROC ;
typedef  scalar_t__ PFNGLGETCOMPRESSEDTEXIMAGEPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVETEXTUREPROC ;
typedef  scalar_t__ PFNGLACTIVETEXTUREPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_3 ; 
 scalar_t__ glActiveTexture ; 
 scalar_t__ glClientActiveTexture ; 
 scalar_t__ glCompressedTexImage1D ; 
 scalar_t__ glCompressedTexImage2D ; 
 scalar_t__ glCompressedTexImage3D ; 
 scalar_t__ glCompressedTexSubImage1D ; 
 scalar_t__ glCompressedTexSubImage2D ; 
 scalar_t__ glCompressedTexSubImage3D ; 
 scalar_t__ glGetCompressedTexImage ; 
 scalar_t__ glLoadTransposeMatrixd ; 
 scalar_t__ glLoadTransposeMatrixf ; 
 scalar_t__ glMultTransposeMatrixd ; 
 scalar_t__ glMultTransposeMatrixf ; 
 scalar_t__ glMultiTexCoord1d ; 
 scalar_t__ glMultiTexCoord1dv ; 
 scalar_t__ glMultiTexCoord1f ; 
 scalar_t__ glMultiTexCoord1fv ; 
 scalar_t__ glMultiTexCoord1i ; 
 scalar_t__ glMultiTexCoord1iv ; 
 scalar_t__ glMultiTexCoord1s ; 
 scalar_t__ glMultiTexCoord1sv ; 
 scalar_t__ glMultiTexCoord2d ; 
 scalar_t__ glMultiTexCoord2dv ; 
 scalar_t__ glMultiTexCoord2f ; 
 scalar_t__ glMultiTexCoord2fv ; 
 scalar_t__ glMultiTexCoord2i ; 
 scalar_t__ glMultiTexCoord2iv ; 
 scalar_t__ glMultiTexCoord2s ; 
 scalar_t__ glMultiTexCoord2sv ; 
 scalar_t__ glMultiTexCoord3d ; 
 scalar_t__ glMultiTexCoord3dv ; 
 scalar_t__ glMultiTexCoord3f ; 
 scalar_t__ glMultiTexCoord3fv ; 
 scalar_t__ glMultiTexCoord3i ; 
 scalar_t__ glMultiTexCoord3iv ; 
 scalar_t__ glMultiTexCoord3s ; 
 scalar_t__ glMultiTexCoord3sv ; 
 scalar_t__ glMultiTexCoord4d ; 
 scalar_t__ glMultiTexCoord4dv ; 
 scalar_t__ glMultiTexCoord4f ; 
 scalar_t__ glMultiTexCoord4fv ; 
 scalar_t__ glMultiTexCoord4i ; 
 scalar_t__ glMultiTexCoord4iv ; 
 scalar_t__ glMultiTexCoord4s ; 
 scalar_t__ glMultiTexCoord4sv ; 
 scalar_t__ glSampleCoverage ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_1_3( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_3) return;
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) load("glActiveTexture", userptr);
    glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) load("glClientActiveTexture", userptr);
    glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) load("glCompressedTexImage1D", userptr);
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load("glCompressedTexImage2D", userptr);
    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) load("glCompressedTexImage3D", userptr);
    glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) load("glCompressedTexSubImage1D", userptr);
    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load("glCompressedTexSubImage2D", userptr);
    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) load("glCompressedTexSubImage3D", userptr);
    glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) load("glGetCompressedTexImage", userptr);
    glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC) load("glLoadTransposeMatrixd", userptr);
    glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC) load("glLoadTransposeMatrixf", userptr);
    glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC) load("glMultTransposeMatrixd", userptr);
    glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC) load("glMultTransposeMatrixf", userptr);
    glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC) load("glMultiTexCoord1d", userptr);
    glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC) load("glMultiTexCoord1dv", userptr);
    glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC) load("glMultiTexCoord1f", userptr);
    glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC) load("glMultiTexCoord1fv", userptr);
    glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC) load("glMultiTexCoord1i", userptr);
    glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC) load("glMultiTexCoord1iv", userptr);
    glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC) load("glMultiTexCoord1s", userptr);
    glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC) load("glMultiTexCoord1sv", userptr);
    glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC) load("glMultiTexCoord2d", userptr);
    glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC) load("glMultiTexCoord2dv", userptr);
    glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC) load("glMultiTexCoord2f", userptr);
    glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC) load("glMultiTexCoord2fv", userptr);
    glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC) load("glMultiTexCoord2i", userptr);
    glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC) load("glMultiTexCoord2iv", userptr);
    glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC) load("glMultiTexCoord2s", userptr);
    glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC) load("glMultiTexCoord2sv", userptr);
    glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC) load("glMultiTexCoord3d", userptr);
    glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC) load("glMultiTexCoord3dv", userptr);
    glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC) load("glMultiTexCoord3f", userptr);
    glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC) load("glMultiTexCoord3fv", userptr);
    glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC) load("glMultiTexCoord3i", userptr);
    glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC) load("glMultiTexCoord3iv", userptr);
    glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC) load("glMultiTexCoord3s", userptr);
    glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC) load("glMultiTexCoord3sv", userptr);
    glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC) load("glMultiTexCoord4d", userptr);
    glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC) load("glMultiTexCoord4dv", userptr);
    glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC) load("glMultiTexCoord4f", userptr);
    glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC) load("glMultiTexCoord4fv", userptr);
    glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC) load("glMultiTexCoord4i", userptr);
    glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC) load("glMultiTexCoord4iv", userptr);
    glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC) load("glMultiTexCoord4s", userptr);
    glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC) load("glMultiTexCoord4sv", userptr);
    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load("glSampleCoverage", userptr);
}