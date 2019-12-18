#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int errnum; scalar_t__ errstr; } ;

/* Variables and functions */
 TYPE_1__* errlist ; 

char *WINS_ErrorMessage( int error ){
	int search = 0;

	if ( !error ) {
		return "No error occurred";
	}

	for ( search = 0; errlist[search].errstr; search++ )
	{
		if ( error == errlist[search].errnum ) {
			return (char *)errlist[search].errstr;
		}
	}  //end for

	return "Unknown error";
}