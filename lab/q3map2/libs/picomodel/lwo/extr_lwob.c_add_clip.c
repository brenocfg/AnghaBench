#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* name; } ;
struct TYPE_16__ {char* prefix; int digits; } ;
struct TYPE_18__ {TYPE_6__ still; TYPE_5__ seq; } ;
struct TYPE_15__ {float val; } ;
struct TYPE_14__ {float val; } ;
struct TYPE_13__ {float val; } ;
struct TYPE_12__ {float val; } ;
struct TYPE_19__ {int index; TYPE_7__ source; int /*<<< orphan*/  type; TYPE_4__ gamma; TYPE_3__ saturation; TYPE_2__ brightness; TYPE_1__ contrast; } ;
typedef  TYPE_8__ lwClip ;

/* Variables and functions */
 int /*<<< orphan*/  ID_ISEQ ; 
 int /*<<< orphan*/  ID_STIL ; 
 TYPE_8__* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  lwListAdd (void**,TYPE_8__*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int add_clip( char *s, lwClip **clist, int *nclips ){
	lwClip *clip;
	char *p;

	clip = _pico_calloc( 1, sizeof( lwClip ) );
	if ( !clip ) {
		return 0;
	}

	clip->contrast.val = 1.0f;
	clip->brightness.val = 1.0f;
	clip->saturation.val = 1.0f;
	clip->gamma.val = 1.0f;

	if ( ( p = strstr( s, "(sequence)" ) ) != NULL ) {
		p[ -1 ] = 0;
		clip->type = ID_ISEQ;
		clip->source.seq.prefix = s;
		clip->source.seq.digits = 3;
	}
	else {
		clip->type = ID_STIL;
		clip->source.still.name = s;
	}

	( *nclips )++;
	clip->index = *nclips;

	lwListAdd( (void **) clist, clip );

	return clip->index;
}