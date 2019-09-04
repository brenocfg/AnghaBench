#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int vec_t ;
typedef  int* vec3_t ;
typedef  int /*<<< orphan*/  tx ;
struct TYPE_7__ {int** vecs; scalar_t__ flags; scalar_t__ value; int nexttexinfo; scalar_t__* texture; } ;
typedef  TYPE_1__ texinfo_t ;
typedef  int /*<<< orphan*/  plane_t ;
struct TYPE_8__ {int* scale; int rotate; float* shift; scalar_t__ flags; scalar_t__ value; scalar_t__* name; } ;
typedef  TYPE_2__ brush_texture_t ;
struct TYPE_9__ {scalar_t__* animname; } ;

/* Variables and functions */
 float DotProduct (int*,int*) ; 
 int FindMiptex (scalar_t__*) ; 
 int Q_PI ; 
 int /*<<< orphan*/  TextureAxisFromPlane (int /*<<< orphan*/ *,int*,int*) ; 
 int cos (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numtexinfo ; 
 int sin (int) ; 
 scalar_t__ strcmp (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__*) ; 
 TYPE_1__* texinfo ; 
 TYPE_3__* textureref ; 

int TexinfoForBrushTexture(plane_t *plane, brush_texture_t *bt, vec3_t origin)
{
	vec3_t	vecs[2];
	int		sv, tv;
	vec_t	ang, sinv, cosv;
	vec_t	ns, nt;
	texinfo_t	tx, *tc;
	int		i, j, k;
	float	shift[2];
	brush_texture_t		anim;
	int				mt;

	if (!bt->name[0])
		return 0;

	memset (&tx, 0, sizeof(tx));
	strcpy (tx.texture, bt->name);

	TextureAxisFromPlane(plane, vecs[0], vecs[1]);

	shift[0] = DotProduct (origin, vecs[0]);
	shift[1] = DotProduct (origin, vecs[1]);

	if (!bt->scale[0])
		bt->scale[0] = 1;
	if (!bt->scale[1])
		bt->scale[1] = 1;


// rotate axis
	if (bt->rotate == 0)
		{ sinv = 0 ; cosv = 1; }
	else if (bt->rotate == 90)
		{ sinv = 1 ; cosv = 0; }
	else if (bt->rotate == 180)
		{ sinv = 0 ; cosv = -1; }
	else if (bt->rotate == 270)
		{ sinv = -1 ; cosv = 0; }
	else
	{	
		ang = bt->rotate / 180 * Q_PI;
		sinv = sin(ang);
		cosv = cos(ang);
	}

	if (vecs[0][0])
		sv = 0;
	else if (vecs[0][1])
		sv = 1;
	else
		sv = 2;
				
	if (vecs[1][0])
		tv = 0;
	else if (vecs[1][1])
		tv = 1;
	else
		tv = 2;
					
	for (i=0 ; i<2 ; i++)
	{
		ns = cosv * vecs[i][sv] - sinv * vecs[i][tv];
		nt = sinv * vecs[i][sv] +  cosv * vecs[i][tv];
		vecs[i][sv] = ns;
		vecs[i][tv] = nt;
	}

	for (i=0 ; i<2 ; i++)
		for (j=0 ; j<3 ; j++)
			tx.vecs[i][j] = vecs[i][j] / bt->scale[i];

	tx.vecs[0][3] = bt->shift[0] + shift[0];
	tx.vecs[1][3] = bt->shift[1] + shift[1];
	tx.flags = bt->flags;
	tx.value = bt->value;

	//
	// find the texinfo
	//
	tc = texinfo;
	for (i=0 ; i<numtexinfo ; i++, tc++)
	{
		if (tc->flags != tx.flags)
			continue;
		if (tc->value != tx.value)
			continue;
		for (j=0 ; j<2 ; j++)
		{
			if (strcmp (tc->texture, tx.texture))
				goto skip;
			for (k=0 ; k<4 ; k++)
			{
				if (tc->vecs[j][k] != tx.vecs[j][k])
					goto skip;
			}
		}
		return i;
skip:;
	}
	*tc = tx;
	numtexinfo++;

	// load the next animation
	mt = FindMiptex (bt->name);
	if (textureref[mt].animname[0])
	{
		anim = *bt;
		strcpy (anim.name, textureref[mt].animname);
		tc->nexttexinfo = TexinfoForBrushTexture (plane, &anim, origin);
	}
	else
		tc->nexttexinfo = -1;


	return i;
}