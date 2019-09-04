#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int texnum; int /*<<< orphan*/  frameUsed; } ;
typedef  TYPE_3__ image_t ;
struct TYPE_15__ {int* currenttextures; size_t currenttmu; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  frameCount; TYPE_2__* dlightImage; TYPE_1__* defaultImage; } ;
struct TYPE_10__ {int texnum; } ;
struct TYPE_9__ {int texnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 TYPE_7__ glState ; 
 int /*<<< orphan*/  qglBindTexture (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* r_nobind ; 
 TYPE_5__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ tr ; 

void GL_Bind( image_t *image ) {
	int texnum;

	if ( !image ) {
		ri.Printf( PRINT_WARNING, "GL_Bind: NULL image\n" );
		texnum = tr.defaultImage->texnum;
	} else {
		texnum = image->texnum;
	}

	if ( r_nobind->integer && tr.dlightImage ) {		// performance evaluation option
		texnum = tr.dlightImage->texnum;
	}

	if ( glState.currenttextures[glState.currenttmu] != texnum ) {
		if ( image ) {
			image->frameUsed = tr.frameCount;
		}
		glState.currenttextures[glState.currenttmu] = texnum;
		qglBindTexture (GL_TEXTURE_2D, texnum);
	}
}