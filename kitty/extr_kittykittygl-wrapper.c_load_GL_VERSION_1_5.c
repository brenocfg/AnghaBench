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
typedef  scalar_t__ PFNGLUNMAPBUFFERPROC ;
typedef  scalar_t__ PFNGLMAPBUFFERPROC ;
typedef  scalar_t__ PFNGLISQUERYPROC ;
typedef  scalar_t__ PFNGLISBUFFERPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTUIVPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTIVPROC ;
typedef  scalar_t__ PFNGLGETQUERYIVPROC ;
typedef  scalar_t__ PFNGLGETBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPOINTERVPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGENQUERIESPROC ;
typedef  scalar_t__ PFNGLGENBUFFERSPROC ;
typedef  scalar_t__ PFNGLENDQUERYPROC ;
typedef  scalar_t__ PFNGLDELETEQUERIESPROC ;
typedef  scalar_t__ PFNGLDELETEBUFFERSPROC ;
typedef  scalar_t__ PFNGLBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLBUFFERDATAPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_5 ; 
 scalar_t__ glad_glBeginQuery ; 
 scalar_t__ glad_glBindBuffer ; 
 scalar_t__ glad_glBufferData ; 
 scalar_t__ glad_glBufferSubData ; 
 scalar_t__ glad_glDeleteBuffers ; 
 scalar_t__ glad_glDeleteQueries ; 
 scalar_t__ glad_glEndQuery ; 
 scalar_t__ glad_glGenBuffers ; 
 scalar_t__ glad_glGenQueries ; 
 scalar_t__ glad_glGetBufferParameteriv ; 
 scalar_t__ glad_glGetBufferPointerv ; 
 scalar_t__ glad_glGetBufferSubData ; 
 scalar_t__ glad_glGetQueryObjectiv ; 
 scalar_t__ glad_glGetQueryObjectuiv ; 
 scalar_t__ glad_glGetQueryiv ; 
 scalar_t__ glad_glIsBuffer ; 
 scalar_t__ glad_glIsQuery ; 
 scalar_t__ glad_glMapBuffer ; 
 scalar_t__ glad_glUnmapBuffer ; 

__attribute__((used)) static void load_GL_VERSION_1_5(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_5) return;
	glad_glGenQueries = (PFNGLGENQUERIESPROC)load("glGenQueries");
	glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC)load("glDeleteQueries");
	glad_glIsQuery = (PFNGLISQUERYPROC)load("glIsQuery");
	glad_glBeginQuery = (PFNGLBEGINQUERYPROC)load("glBeginQuery");
	glad_glEndQuery = (PFNGLENDQUERYPROC)load("glEndQuery");
	glad_glGetQueryiv = (PFNGLGETQUERYIVPROC)load("glGetQueryiv");
	glad_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)load("glGetQueryObjectiv");
	glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)load("glGetQueryObjectuiv");
	glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
	glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
	glad_glIsBuffer = (PFNGLISBUFFERPROC)load("glIsBuffer");
	glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)load("glBufferSubData");
	glad_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)load("glGetBufferSubData");
	glad_glMapBuffer = (PFNGLMAPBUFFERPROC)load("glMapBuffer");
	glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)load("glUnmapBuffer");
	glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)load("glGetBufferParameteriv");
	glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)load("glGetBufferPointerv");
}