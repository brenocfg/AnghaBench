#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  genFunc_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GF_INVERSE_SAWTOOTH ; 
 int /*<<< orphan*/  GF_NOISE ; 
 int /*<<< orphan*/  GF_SAWTOOTH ; 
 int /*<<< orphan*/  GF_SIN ; 
 int /*<<< orphan*/  GF_SQUARE ; 
 int /*<<< orphan*/  GF_TRIANGLE ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  Q_stricmp (char const*,char*) ; 
 TYPE_2__ ri ; 
 TYPE_1__ shader ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static genFunc_t NameToGenFunc( const char *funcname )
{
	if ( !Q_stricmp( funcname, "sin" ) )
	{
		return GF_SIN;
	}
	else if ( !Q_stricmp( funcname, "square" ) )
	{
		return GF_SQUARE;
	}
	else if ( !Q_stricmp( funcname, "triangle" ) )
	{
		return GF_TRIANGLE;
	}
	else if ( !Q_stricmp( funcname, "sawtooth" ) )
	{
		return GF_SAWTOOTH;
	}
	else if ( !Q_stricmp( funcname, "inversesawtooth" ) )
	{
		return GF_INVERSE_SAWTOOTH;
	}
	else if ( !Q_stricmp( funcname, "noise" ) )
	{
		return GF_NOISE;
	}

	ri.Printf( PRINT_WARNING, "WARNING: invalid genfunc name '%s' in shader '%s'\n", funcname, shader.name );
	return GF_SIN;
}