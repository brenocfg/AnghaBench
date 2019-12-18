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
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_5 ; 
 scalar_t__ glBeginQuery ; 
 scalar_t__ glBindBuffer ; 
 scalar_t__ glBufferData ; 
 scalar_t__ glBufferSubData ; 
 scalar_t__ glDeleteBuffers ; 
 scalar_t__ glDeleteQueries ; 
 scalar_t__ glEndQuery ; 
 scalar_t__ glGenBuffers ; 
 scalar_t__ glGenQueries ; 
 scalar_t__ glGetBufferParameteriv ; 
 scalar_t__ glGetBufferPointerv ; 
 scalar_t__ glGetBufferSubData ; 
 scalar_t__ glGetQueryObjectiv ; 
 scalar_t__ glGetQueryObjectuiv ; 
 scalar_t__ glGetQueryiv ; 
 scalar_t__ glIsBuffer ; 
 scalar_t__ glIsQuery ; 
 scalar_t__ glMapBuffer ; 
 scalar_t__ glUnmapBuffer ; 

__attribute__((used)) static void glad_gl_load_GL_VERSION_1_5( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_5) return;
    glBeginQuery = (PFNGLBEGINQUERYPROC) load("glBeginQuery", userptr);
    glBindBuffer = (PFNGLBINDBUFFERPROC) load("glBindBuffer", userptr);
    glBufferData = (PFNGLBUFFERDATAPROC) load("glBufferData", userptr);
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) load("glBufferSubData", userptr);
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load("glDeleteBuffers", userptr);
    glDeleteQueries = (PFNGLDELETEQUERIESPROC) load("glDeleteQueries", userptr);
    glEndQuery = (PFNGLENDQUERYPROC) load("glEndQuery", userptr);
    glGenBuffers = (PFNGLGENBUFFERSPROC) load("glGenBuffers", userptr);
    glGenQueries = (PFNGLGENQUERIESPROC) load("glGenQueries", userptr);
    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load("glGetBufferParameteriv", userptr);
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) load("glGetBufferPointerv", userptr);
    glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) load("glGetBufferSubData", userptr);
    glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) load("glGetQueryObjectiv", userptr);
    glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) load("glGetQueryObjectuiv", userptr);
    glGetQueryiv = (PFNGLGETQUERYIVPROC) load("glGetQueryiv", userptr);
    glIsBuffer = (PFNGLISBUFFERPROC) load("glIsBuffer", userptr);
    glIsQuery = (PFNGLISQUERYPROC) load("glIsQuery", userptr);
    glMapBuffer = (PFNGLMAPBUFFERPROC) load("glMapBuffer", userptr);
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) load("glUnmapBuffer", userptr);
}