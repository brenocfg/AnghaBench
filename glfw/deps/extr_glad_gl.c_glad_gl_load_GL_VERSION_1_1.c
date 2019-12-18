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
typedef  scalar_t__ PFNGLVERTEXPOINTERPROC ;
typedef  scalar_t__ PFNGLTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERPROC ;
typedef  scalar_t__ PFNGLPUSHCLIENTATTRIBPROC ;
typedef  scalar_t__ PFNGLPRIORITIZETEXTURESPROC ;
typedef  scalar_t__ PFNGLPOPCLIENTATTRIBPROC ;
typedef  scalar_t__ PFNGLPOLYGONOFFSETPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERPROC ;
typedef  scalar_t__ PFNGLISTEXTUREPROC ;
typedef  scalar_t__ PFNGLINTERLEAVEDARRAYSPROC ;
typedef  scalar_t__ PFNGLINDEXUBVPROC ;
typedef  scalar_t__ PFNGLINDEXUBPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTERPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVPROC ;
typedef  scalar_t__ PFNGLGENTEXTURESPROC ;
typedef  scalar_t__ PFNGLENABLECLIENTSTATEPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTERPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSPROC ;
typedef  scalar_t__ PFNGLDISABLECLIENTSTATEPROC ;
typedef  scalar_t__ PFNGLDELETETEXTURESPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERPROC ;
typedef  scalar_t__ PFNGLBINDTEXTUREPROC ;
typedef  scalar_t__ PFNGLARRAYELEMENTPROC ;
typedef  scalar_t__ PFNGLARETEXTURESRESIDENTPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_1 ; 
 scalar_t__ glAreTexturesResident ; 
 scalar_t__ glArrayElement ; 
 scalar_t__ glBindTexture ; 
 scalar_t__ glColorPointer ; 
 scalar_t__ glCopyTexImage1D ; 
 scalar_t__ glCopyTexImage2D ; 
 scalar_t__ glCopyTexSubImage1D ; 
 scalar_t__ glCopyTexSubImage2D ; 
 scalar_t__ glDeleteTextures ; 
 scalar_t__ glDisableClientState ; 
 scalar_t__ glDrawArrays ; 
 scalar_t__ glDrawElements ; 
 scalar_t__ glEdgeFlagPointer ; 
 scalar_t__ glEnableClientState ; 
 scalar_t__ glGenTextures ; 
 scalar_t__ glGetPointerv ; 
 scalar_t__ glIndexPointer ; 
 scalar_t__ glIndexub ; 
 scalar_t__ glIndexubv ; 
 scalar_t__ glInterleavedArrays ; 
 scalar_t__ glIsTexture ; 
 scalar_t__ glNormalPointer ; 
 scalar_t__ glPolygonOffset ; 
 scalar_t__ glPopClientAttrib ; 
 scalar_t__ glPrioritizeTextures ; 
 scalar_t__ glPushClientAttrib ; 
 scalar_t__ glTexCoordPointer ; 
 scalar_t__ glTexSubImage1D ; 
 scalar_t__ glTexSubImage2D ; 
 scalar_t__ glVertexPointer ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_1_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_1) return;
    glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC) load("glAreTexturesResident", userptr);
    glArrayElement = (PFNGLARRAYELEMENTPROC) load("glArrayElement", userptr);
    glBindTexture = (PFNGLBINDTEXTUREPROC) load("glBindTexture", userptr);
    glColorPointer = (PFNGLCOLORPOINTERPROC) load("glColorPointer", userptr);
    glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) load("glCopyTexImage1D", userptr);
    glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load("glCopyTexImage2D", userptr);
    glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) load("glCopyTexSubImage1D", userptr);
    glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load("glCopyTexSubImage2D", userptr);
    glDeleteTextures = (PFNGLDELETETEXTURESPROC) load("glDeleteTextures", userptr);
    glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC) load("glDisableClientState", userptr);
    glDrawArrays = (PFNGLDRAWARRAYSPROC) load("glDrawArrays", userptr);
    glDrawElements = (PFNGLDRAWELEMENTSPROC) load("glDrawElements", userptr);
    glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC) load("glEdgeFlagPointer", userptr);
    glEnableClientState = (PFNGLENABLECLIENTSTATEPROC) load("glEnableClientState", userptr);
    glGenTextures = (PFNGLGENTEXTURESPROC) load("glGenTextures", userptr);
    glGetPointerv = (PFNGLGETPOINTERVPROC) load("glGetPointerv", userptr);
    glIndexPointer = (PFNGLINDEXPOINTERPROC) load("glIndexPointer", userptr);
    glIndexub = (PFNGLINDEXUBPROC) load("glIndexub", userptr);
    glIndexubv = (PFNGLINDEXUBVPROC) load("glIndexubv", userptr);
    glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC) load("glInterleavedArrays", userptr);
    glIsTexture = (PFNGLISTEXTUREPROC) load("glIsTexture", userptr);
    glNormalPointer = (PFNGLNORMALPOINTERPROC) load("glNormalPointer", userptr);
    glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) load("glPolygonOffset", userptr);
    glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC) load("glPopClientAttrib", userptr);
    glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC) load("glPrioritizeTextures", userptr);
    glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC) load("glPushClientAttrib", userptr);
    glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC) load("glTexCoordPointer", userptr);
    glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) load("glTexSubImage1D", userptr);
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load("glTexSubImage2D", userptr);
    glVertexPointer = (PFNGLVERTEXPOINTERPROC) load("glVertexPointer", userptr);
}