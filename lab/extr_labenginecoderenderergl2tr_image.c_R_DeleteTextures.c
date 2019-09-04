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
struct TYPE_4__ {int /*<<< orphan*/  texnum; } ;
struct TYPE_3__ {int numImages; TYPE_2__** images; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_2__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GL_BindNullTextures () ; 
 int /*<<< orphan*/  qglDeleteTextures (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ tr ; 

void R_DeleteTextures( void ) {
	int		i;

	for ( i=0; i<tr.numImages ; i++ ) {
		qglDeleteTextures( 1, &tr.images[i]->texnum );
	}
	Com_Memset( tr.images, 0, sizeof( tr.images ) );

	tr.numImages = 0;

	GL_BindNullTextures();
}