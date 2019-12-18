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
typedef  scalar_t__ PFNGLUNIFORMBLOCKBINDINGPROC ;
typedef  scalar_t__ PFNGLTEXBUFFERPROC ;
typedef  scalar_t__ PFNGLPRIMITIVERESTARTINDEXPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMINDICESPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMBLOCKINDEXPROC ;
typedef  scalar_t__ PFNGLGETINTEGERI_VPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMSIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKIVPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINSTANCEDPROC ;
typedef  scalar_t__ PFNGLCOPYBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERRANGEPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERBASEPROC ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_3_1 ; 
 scalar_t__ glBindBufferBase ; 
 scalar_t__ glBindBufferRange ; 
 scalar_t__ glCopyBufferSubData ; 
 scalar_t__ glDrawArraysInstanced ; 
 scalar_t__ glDrawElementsInstanced ; 
 scalar_t__ glGetActiveUniformBlockName ; 
 scalar_t__ glGetActiveUniformBlockiv ; 
 scalar_t__ glGetActiveUniformName ; 
 scalar_t__ glGetActiveUniformsiv ; 
 scalar_t__ glGetIntegeri_v ; 
 scalar_t__ glGetUniformBlockIndex ; 
 scalar_t__ glGetUniformIndices ; 
 scalar_t__ glPrimitiveRestartIndex ; 
 scalar_t__ glTexBuffer ; 
 scalar_t__ glUniformBlockBinding ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_3_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_1) return;
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load("glBindBufferBase", userptr);
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) load("glBindBufferRange", userptr);
    glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) load("glCopyBufferSubData", userptr);
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) load("glDrawArraysInstanced", userptr);
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) load("glDrawElementsInstanced", userptr);
    glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) load("glGetActiveUniformBlockName", userptr);
    glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) load("glGetActiveUniformBlockiv", userptr);
    glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) load("glGetActiveUniformName", userptr);
    glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) load("glGetActiveUniformsiv", userptr);
    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) load("glGetIntegeri_v", userptr);
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) load("glGetUniformBlockIndex", userptr);
    glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) load("glGetUniformIndices", userptr);
    glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) load("glPrimitiveRestartIndex", userptr);
    glTexBuffer = (PFNGLTEXBUFFERPROC) load("glTexBuffer", userptr);
    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) load("glUniformBlockBinding", userptr);
}