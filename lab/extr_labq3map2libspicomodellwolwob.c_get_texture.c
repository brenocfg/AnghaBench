#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* name; } ;
struct TYPE_14__ {float val; } ;
struct TYPE_15__ {int projection; float aa_strength; TYPE_4__ amplitude; } ;
struct TYPE_17__ {TYPE_6__ proc; TYPE_5__ imap; } ;
struct TYPE_13__ {float val; } ;
struct TYPE_11__ {float* val; } ;
struct TYPE_12__ {TYPE_1__ size; } ;
struct TYPE_18__ {int enabled; TYPE_7__ param; int /*<<< orphan*/  type; TYPE_3__ opacity; TYPE_2__ tmap; } ;
typedef  TYPE_8__ lwTexture ;

/* Variables and functions */
 int /*<<< orphan*/  ID_IMAP ; 
 int /*<<< orphan*/  ID_PROC ; 
 TYPE_8__* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_free (char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static lwTexture *get_texture( char *s ){
	lwTexture *tex;

	tex = _pico_calloc( 1, sizeof( lwTexture ) );
	if ( !tex ) {
		return NULL;
	}

	tex->tmap.size.val[ 0 ] =
		tex->tmap.size.val[ 1 ] =
			tex->tmap.size.val[ 2 ] = 1.0f;
	tex->opacity.val = 1.0f;
	tex->enabled = 1;

	if ( strstr( s, "Image Map" ) ) {
		tex->type = ID_IMAP;
		if ( strstr( s, "Planar" ) ) {
			tex->param.imap.projection = 0;
		}
		else if ( strstr( s, "Cylindrical" ) ) {
			tex->param.imap.projection = 1;
		}
		else if ( strstr( s, "Spherical" ) ) {
			tex->param.imap.projection = 2;
		}
		else if ( strstr( s, "Cubic" ) ) {
			tex->param.imap.projection = 3;
		}
		else if ( strstr( s, "Front" ) ) {
			tex->param.imap.projection = 4;
		}
		tex->param.imap.aa_strength = 1.0f;
		tex->param.imap.amplitude.val = 1.0f;
		_pico_free( s );
	}
	else {
		tex->type = ID_PROC;
		tex->param.proc.name = s;
	}

	return tex;
}