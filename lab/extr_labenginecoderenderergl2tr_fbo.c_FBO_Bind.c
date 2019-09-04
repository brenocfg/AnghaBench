#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  framebufferObject; } ;
struct TYPE_10__ {TYPE_1__* currentFBO; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  frameBuffer; } ;
typedef  TYPE_1__ FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GLimp_LogComment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 TYPE_5__ glRefConfig ; 
 TYPE_4__ glState ; 
 TYPE_3__* r_logFile ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

void FBO_Bind(FBO_t * fbo)
{
	if (!glRefConfig.framebufferObject)
	{
		ri.Printf(PRINT_WARNING, "FBO_Bind() called without framebuffers enabled!\n");
		return;
	}

	if (glState.currentFBO == fbo)
		return;
		
	if (r_logFile->integer)
	{
		// don't just call LogComment, or we will get a call to va() every frame!
		GLimp_LogComment(va("--- FBO_Bind( %s ) ---\n", fbo ? fbo->name : "NULL"));
	}

	GL_BindFramebuffer(GL_FRAMEBUFFER, fbo ? fbo->frameBuffer : 0);
	glState.currentFBO = fbo;
}