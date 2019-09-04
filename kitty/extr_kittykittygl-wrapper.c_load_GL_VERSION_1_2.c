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
typedef  scalar_t__ PFNGLTEXSUBIMAGE3DPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE3DPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTSPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE3DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_2 ; 
 scalar_t__ glad_glCopyTexSubImage3D ; 
 scalar_t__ glad_glDrawRangeElements ; 
 scalar_t__ glad_glTexImage3D ; 
 scalar_t__ glad_glTexSubImage3D ; 

__attribute__((used)) static void load_GL_VERSION_1_2(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_2) return;
	glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)load("glDrawRangeElements");
	glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC)load("glTexImage3D");
	glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)load("glTexSubImage3D");
	glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)load("glCopyTexSubImage3D");
}