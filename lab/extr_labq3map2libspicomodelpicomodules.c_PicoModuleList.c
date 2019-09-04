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
typedef  int /*<<< orphan*/  picoModule_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** picoModules ; 

const picoModule_t **PicoModuleList( int *numModules ) {
	/* get module count */
	if ( numModules != NULL ) {
		for ( ( *numModules ) = 0; picoModules[ *numModules ] != NULL; ( *numModules )++ ) ;
	}

	/* return list of modules */
	return (const picoModule_t**) picoModules;
}