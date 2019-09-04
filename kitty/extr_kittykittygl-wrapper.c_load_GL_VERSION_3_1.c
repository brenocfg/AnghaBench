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
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_3_1 ; 
 scalar_t__ glad_glBindBufferBase ; 
 scalar_t__ glad_glBindBufferRange ; 
 scalar_t__ glad_glCopyBufferSubData ; 
 scalar_t__ glad_glDrawArraysInstanced ; 
 scalar_t__ glad_glDrawElementsInstanced ; 
 scalar_t__ glad_glGetActiveUniformBlockName ; 
 scalar_t__ glad_glGetActiveUniformBlockiv ; 
 scalar_t__ glad_glGetActiveUniformName ; 
 scalar_t__ glad_glGetActiveUniformsiv ; 
 scalar_t__ glad_glGetIntegeri_v ; 
 scalar_t__ glad_glGetUniformBlockIndex ; 
 scalar_t__ glad_glGetUniformIndices ; 
 scalar_t__ glad_glPrimitiveRestartIndex ; 
 scalar_t__ glad_glTexBuffer ; 
 scalar_t__ glad_glUniformBlockBinding ; 

__attribute__((used)) static void load_GL_VERSION_3_1(GLADloadproc load) {
	if(!GLAD_GL_VERSION_3_1) return;
	glad_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)load("glDrawArraysInstanced");
	glad_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)load("glDrawElementsInstanced");
	glad_glTexBuffer = (PFNGLTEXBUFFERPROC)load("glTexBuffer");
	glad_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)load("glPrimitiveRestartIndex");
	glad_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)load("glCopyBufferSubData");
	glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)load("glGetUniformIndices");
	glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)load("glGetActiveUniformsiv");
	glad_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)load("glGetActiveUniformName");
	glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)load("glGetUniformBlockIndex");
	glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)load("glGetActiveUniformBlockiv");
	glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)load("glGetActiveUniformBlockName");
	glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)load("glUniformBlockBinding");
	glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)load("glBindBufferRange");
	glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)load("glBindBufferBase");
	glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)load("glGetIntegeri_v");
}