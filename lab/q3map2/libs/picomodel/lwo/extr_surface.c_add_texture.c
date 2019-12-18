#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int chan; } ;
typedef  TYPE_13__ lwTexture ;
struct TYPE_20__ {TYPE_13__* tex; } ;
struct TYPE_19__ {TYPE_13__* tex; } ;
struct TYPE_18__ {TYPE_13__* tex; } ;
struct TYPE_30__ {TYPE_13__* tex; } ;
struct TYPE_31__ {TYPE_8__ val; } ;
struct TYPE_28__ {TYPE_13__* tex; } ;
struct TYPE_29__ {TYPE_6__ val; } ;
struct TYPE_27__ {TYPE_13__* tex; } ;
struct TYPE_26__ {TYPE_13__* tex; } ;
struct TYPE_25__ {TYPE_13__* tex; } ;
struct TYPE_24__ {TYPE_13__* tex; } ;
struct TYPE_23__ {TYPE_13__* tex; } ;
struct TYPE_22__ {TYPE_12__ bump; TYPE_11__ translucency; TYPE_10__ eta; TYPE_9__ transparency; TYPE_7__ reflection; TYPE_5__ glossiness; TYPE_4__ specularity; TYPE_3__ diffuse; TYPE_2__ luminosity; TYPE_1__ color; } ;
typedef  TYPE_14__ lwSurface ;
typedef  int /*<<< orphan*/  ListCompareFunc ;

/* Variables and functions */
#define  ID_BUMP 137 
#define  ID_COLR 136 
#define  ID_DIFF 135 
#define  ID_GLOS 134 
#define  ID_LUMI 133 
#define  ID_REFL 132 
#define  ID_RIND 131 
#define  ID_SPEC 130 
#define  ID_TRAN 129 
#define  ID_TRNL 128 
 scalar_t__ compare_textures ; 
 int /*<<< orphan*/  lwListInsert (void**,TYPE_13__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_texture( lwSurface *surf, lwTexture *tex ){
	lwTexture **list;

	switch ( tex->chan ) {
	case ID_COLR:  list = &surf->color.tex;             break;
	case ID_LUMI:  list = &surf->luminosity.tex;        break;
	case ID_DIFF:  list = &surf->diffuse.tex;           break;
	case ID_SPEC:  list = &surf->specularity.tex;       break;
	case ID_GLOS:  list = &surf->glossiness.tex;        break;
	case ID_REFL:  list = &surf->reflection.val.tex;    break;
	case ID_TRAN:  list = &surf->transparency.val.tex;  break;
	case ID_RIND:  list = &surf->eta.tex;               break;
	case ID_TRNL:  list = &surf->translucency.tex;      break;
	case ID_BUMP:  list = &surf->bump.tex;              break;
	default:  return 0;
	}

	lwListInsert( (void **) list, tex, (ListCompareFunc) compare_textures );
	return 1;
}