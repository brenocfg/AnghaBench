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

/* Variables and functions */
 int /*<<< orphan*/  ASE_KeyMAP_DIFFUSE ; 
 int /*<<< orphan*/  ASE_ParseBracedBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void ASE_KeyMATERIAL( const char *token ){
	if ( !strcmp( token, "*MAP_DIFFUSE" ) ) {
		ASE_ParseBracedBlock( ASE_KeyMAP_DIFFUSE );
	}
	else
	{
	}
}