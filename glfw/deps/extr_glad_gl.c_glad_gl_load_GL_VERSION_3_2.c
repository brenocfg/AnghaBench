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
typedef  scalar_t__ PFNGLWAITSYNCPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE2DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKIPROC ;
typedef  scalar_t__ PFNGLPROVOKINGVERTEXPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLISSYNCPROC ;
typedef  scalar_t__ PFNGLGETSYNCIVPROC ;
typedef  scalar_t__ PFNGLGETMULTISAMPLEFVPROC ;
typedef  scalar_t__ PFNGLGETINTEGER64VPROC ;
typedef  scalar_t__ PFNGLGETINTEGER64I_VPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERI64VPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREPROC ;
typedef  scalar_t__ PFNGLFENCESYNCPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDELETESYNCPROC ;
typedef  scalar_t__ PFNGLCLIENTWAITSYNCPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_3_2 ; 
 scalar_t__ glClientWaitSync ; 
 scalar_t__ glDeleteSync ; 
 scalar_t__ glDrawElementsBaseVertex ; 
 scalar_t__ glDrawElementsInstancedBaseVertex ; 
 scalar_t__ glDrawRangeElementsBaseVertex ; 
 scalar_t__ glFenceSync ; 
 scalar_t__ glFramebufferTexture ; 
 scalar_t__ glGetBufferParameteri64v ; 
 scalar_t__ glGetInteger64i_v ; 
 scalar_t__ glGetInteger64v ; 
 scalar_t__ glGetMultisamplefv ; 
 scalar_t__ glGetSynciv ; 
 scalar_t__ glIsSync ; 
 scalar_t__ glMultiDrawElementsBaseVertex ; 
 scalar_t__ glProvokingVertex ; 
 scalar_t__ glSampleMaski ; 
 scalar_t__ glTexImage2DMultisample ; 
 scalar_t__ glTexImage3DMultisample ; 
 scalar_t__ glWaitSync ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_3_2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_2) return;
    glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) load("glClientWaitSync", userptr);
    glDeleteSync = (PFNGLDELETESYNCPROC) load("glDeleteSync", userptr);
    glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) load("glDrawElementsBaseVertex", userptr);
    glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) load("glDrawElementsInstancedBaseVertex", userptr);
    glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) load("glDrawRangeElementsBaseVertex", userptr);
    glFenceSync = (PFNGLFENCESYNCPROC) load("glFenceSync", userptr);
    glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) load("glFramebufferTexture", userptr);
    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) load("glGetBufferParameteri64v", userptr);
    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) load("glGetInteger64i_v", userptr);
    glGetInteger64v = (PFNGLGETINTEGER64VPROC) load("glGetInteger64v", userptr);
    glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) load("glGetMultisamplefv", userptr);
    glGetSynciv = (PFNGLGETSYNCIVPROC) load("glGetSynciv", userptr);
    glIsSync = (PFNGLISSYNCPROC) load("glIsSync", userptr);
    glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) load("glMultiDrawElementsBaseVertex", userptr);
    glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) load("glProvokingVertex", userptr);
    glSampleMaski = (PFNGLSAMPLEMASKIPROC) load("glSampleMaski", userptr);
    glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) load("glTexImage2DMultisample", userptr);
    glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) load("glTexImage3DMultisample", userptr);
    glWaitSync = (PFNGLWAITSYNCPROC) load("glWaitSync", userptr);
}