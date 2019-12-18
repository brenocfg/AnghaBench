#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ w; } ;
typedef  TYPE_1__ face_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void    FreeBspFace( face_t *f ) {
	if ( f->w ) {
		FreeWinding( f->w );
	}
	free( f );
}