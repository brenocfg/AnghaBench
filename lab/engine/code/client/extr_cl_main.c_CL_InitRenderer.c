#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vidWidth; } ;
struct TYPE_8__ {TYPE_1__ glconfig; int /*<<< orphan*/  consoleShader; int /*<<< orphan*/  whiteShader; int /*<<< orphan*/  charSetShader; } ;
struct TYPE_7__ {int widthInChars; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* RegisterShader ) (char*) ;int /*<<< orphan*/  (* BeginRegistration ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int SMALLCHAR_WIDTH ; 
 TYPE_4__ cls ; 
 TYPE_3__ g_consoleField ; 
 int g_console_field_width ; 
 TYPE_2__ re ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  stub3 (char*) ; 
 int /*<<< orphan*/  stub4 (char*) ; 

void CL_InitRenderer( void ) {
	// this sets up the renderer and calls R_Init
	re.BeginRegistration( &cls.glconfig );

	// load character sets
	cls.charSetShader = re.RegisterShader( "gfx/2d/bigchars" );
	cls.whiteShader = re.RegisterShader( "white" );
	cls.consoleShader = re.RegisterShader( "console" );
	g_console_field_width = cls.glconfig.vidWidth / SMALLCHAR_WIDTH - 2;
	g_consoleField.widthInChars = g_console_field_width;
}