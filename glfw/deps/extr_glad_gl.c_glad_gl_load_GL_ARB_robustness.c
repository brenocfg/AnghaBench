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
typedef  scalar_t__ PFNGLREADNPIXELSPROC ;
typedef  scalar_t__ PFNGLREADNPIXELSARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMFVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMDVARBPROC ;
typedef  scalar_t__ PFNGLGETNTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNSEPARABLEFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNPOLYGONSTIPPLEARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUSVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMINMAXARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPIVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPDVARBPROC ;
typedef  scalar_t__ PFNGLGETNHISTOGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETNCONVOLUTIONFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNCOLORTABLEARBPROC ;
typedef  scalar_t__ PFNGLGETGRAPHICSRESETSTATUSARBPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_robustness ; 
 scalar_t__ glGetGraphicsResetStatusARB ; 
 scalar_t__ glGetnColorTableARB ; 
 scalar_t__ glGetnCompressedTexImageARB ; 
 scalar_t__ glGetnConvolutionFilterARB ; 
 scalar_t__ glGetnHistogramARB ; 
 scalar_t__ glGetnMapdvARB ; 
 scalar_t__ glGetnMapfvARB ; 
 scalar_t__ glGetnMapivARB ; 
 scalar_t__ glGetnMinmaxARB ; 
 scalar_t__ glGetnPixelMapfvARB ; 
 scalar_t__ glGetnPixelMapuivARB ; 
 scalar_t__ glGetnPixelMapusvARB ; 
 scalar_t__ glGetnPolygonStippleARB ; 
 scalar_t__ glGetnSeparableFilterARB ; 
 scalar_t__ glGetnTexImageARB ; 
 scalar_t__ glGetnUniformdvARB ; 
 scalar_t__ glGetnUniformfvARB ; 
 scalar_t__ glGetnUniformivARB ; 
 scalar_t__ glGetnUniformuivARB ; 
 scalar_t__ glReadnPixels ; 
 scalar_t__ glReadnPixelsARB ; 

__attribute__((used)) static void glad_gl_load_GL_ARB_robustness( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ARB_robustness) return;
    glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC) load("glGetGraphicsResetStatusARB", userptr);
    glGetnColorTableARB = (PFNGLGETNCOLORTABLEARBPROC) load("glGetnColorTableARB", userptr);
    glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC) load("glGetnCompressedTexImageARB", userptr);
    glGetnConvolutionFilterARB = (PFNGLGETNCONVOLUTIONFILTERARBPROC) load("glGetnConvolutionFilterARB", userptr);
    glGetnHistogramARB = (PFNGLGETNHISTOGRAMARBPROC) load("glGetnHistogramARB", userptr);
    glGetnMapdvARB = (PFNGLGETNMAPDVARBPROC) load("glGetnMapdvARB", userptr);
    glGetnMapfvARB = (PFNGLGETNMAPFVARBPROC) load("glGetnMapfvARB", userptr);
    glGetnMapivARB = (PFNGLGETNMAPIVARBPROC) load("glGetnMapivARB", userptr);
    glGetnMinmaxARB = (PFNGLGETNMINMAXARBPROC) load("glGetnMinmaxARB", userptr);
    glGetnPixelMapfvARB = (PFNGLGETNPIXELMAPFVARBPROC) load("glGetnPixelMapfvARB", userptr);
    glGetnPixelMapuivARB = (PFNGLGETNPIXELMAPUIVARBPROC) load("glGetnPixelMapuivARB", userptr);
    glGetnPixelMapusvARB = (PFNGLGETNPIXELMAPUSVARBPROC) load("glGetnPixelMapusvARB", userptr);
    glGetnPolygonStippleARB = (PFNGLGETNPOLYGONSTIPPLEARBPROC) load("glGetnPolygonStippleARB", userptr);
    glGetnSeparableFilterARB = (PFNGLGETNSEPARABLEFILTERARBPROC) load("glGetnSeparableFilterARB", userptr);
    glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC) load("glGetnTexImageARB", userptr);
    glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC) load("glGetnUniformdvARB", userptr);
    glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC) load("glGetnUniformfvARB", userptr);
    glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC) load("glGetnUniformivARB", userptr);
    glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC) load("glGetnUniformuivARB", userptr);
    glReadnPixels = (PFNGLREADNPIXELSPROC) load("glReadnPixels", userptr);
    glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC) load("glReadnPixelsARB", userptr);
}