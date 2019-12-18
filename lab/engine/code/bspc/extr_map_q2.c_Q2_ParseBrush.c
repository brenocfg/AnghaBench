#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_24__ {int intvalue; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_25__ {int contents; int surf; int planenum; int /*<<< orphan*/  texinfo; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ side_t ;
typedef  int /*<<< orphan*/  script_t ;
struct TYPE_26__ {int entitynum; int leafnum; int numsides; int contents; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; scalar_t__ brushnum; TYPE_2__* original_sides; } ;
typedef  TYPE_3__ mapbrush_t ;
struct TYPE_27__ {int /*<<< orphan*/  numbrushes; scalar_t__ firstbrush; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_28__ {int flags; int value; int /*<<< orphan*/  name; void** scale; void* rotate; void** shift; } ;
typedef  TYPE_5__ brush_texture_t ;
struct TYPE_30__ {int /*<<< orphan*/  origin; } ;
struct TYPE_29__ {int flags; int value; int contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CreateMapBrushes (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  AddBrushBevels (TYPE_3__*) ; 
 scalar_t__ BrushExists (TYPE_3__*) ; 
 int CONTENTS_DETAIL ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_MIST ; 
 int CONTENTS_MONSTERCLIP ; 
 int CONTENTS_ORIGIN ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 int FindMiptex (int /*<<< orphan*/ ) ; 
 int LAST_VISIBLE_CONTENTS ; 
 int /*<<< orphan*/  Log_Print (char*,int,scalar_t__) ; 
 size_t MAX_MAPFILE_BRUSHES ; 
 size_t MAX_MAPFILE_BRUSHSIDES ; 
 int /*<<< orphan*/  MakeBrushWindings (TYPE_3__*) ; 
 scalar_t__ PS_CheckTokenType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PS_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PS_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PS_ExpectTokenType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PS_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int PlaneFromPoints (int*,int*,int*) ; 
 int Q2_BrushContents (TYPE_3__*) ; 
 int /*<<< orphan*/  SFL_TEXTURED ; 
 int SURF_HINT ; 
 int SURF_SKIP ; 
 int SURF_TRANS33 ; 
 int SURF_TRANS66 ; 
 int /*<<< orphan*/  SetKeyValue (TYPE_9__*,char*,char*) ; 
 int /*<<< orphan*/  TEXINFO_NODE ; 
 int /*<<< orphan*/  TT_NUMBER ; 
 int /*<<< orphan*/  TexinfoForBrushTexture (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,double,scalar_t__*) ; 
 void* atof (int /*<<< orphan*/ ) ; 
 void* atol (int /*<<< orphan*/ ) ; 
 TYPE_2__* brushsides ; 
 int /*<<< orphan*/  c_clipbrushes ; 
 int /*<<< orphan*/  c_squattbrushes ; 
 scalar_t__ create_aas ; 
 TYPE_9__* entities ; 
 scalar_t__ fulldetail ; 
 TYPE_3__* mapbrushes ; 
 int /*<<< orphan*/ * mapplanes ; 
 scalar_t__ nodetail ; 
 scalar_t__ nowater ; 
 int num_entities ; 
 size_t nummapbrushes ; 
 size_t nummapbrushsides ; 
 TYPE_5__* side_brushtextures ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* textureref ; 
 int /*<<< orphan*/  vec3_origin ; 

void Q2_ParseBrush (script_t *script, entity_t *mapent)
{
	mapbrush_t *b;
	int i, j, k;
	int mt;
	side_t *side, *s2;
	int planenum;
	brush_texture_t td;
	int planepts[3][3];
	token_t token;

	if (nummapbrushes >= MAX_MAPFILE_BRUSHES)
		Error ("nummapbrushes == MAX_MAPFILE_BRUSHES");

	b = &mapbrushes[nummapbrushes];
	b->original_sides = &brushsides[nummapbrushsides];
	b->entitynum = num_entities-1;
	b->brushnum = nummapbrushes - mapent->firstbrush;
	b->leafnum = -1;

	do
	{
		if (!PS_ReadToken(script, &token))
			break;
		if (!strcmp(token.string, "}") )
			break;

		//IDBUG: mixed use of MAX_MAPFILE_? and MAX_MAP_? this could
		//			lead to out of bound indexing of the arrays
		if (nummapbrushsides >= MAX_MAPFILE_BRUSHSIDES)
			Error ("MAX_MAPFILE_BRUSHSIDES");
		side = &brushsides[nummapbrushsides];

		//read the three point plane definition
		for (i = 0; i < 3; i++)
		{
			if (i != 0) PS_ExpectTokenString(script, "(");
			for (j = 0; j < 3; j++)
			{
				PS_ExpectAnyToken(script, &token);
				planepts[i][j] = atof(token.string);
			} //end for
			PS_ExpectTokenString(script, ")");
		} //end for

		//
		//read the texturedef
		//
		PS_ExpectAnyToken(script, &token);
		strcpy(td.name, token.string);

		PS_ExpectAnyToken(script, &token);
		td.shift[0] = atol(token.string);
		PS_ExpectAnyToken(script, &token);
		td.shift[1] = atol(token.string);
		PS_ExpectAnyToken(script, &token);
		td.rotate = atol(token.string);
		PS_ExpectAnyToken(script, &token);
		td.scale[0] = atof(token.string);
		PS_ExpectAnyToken(script, &token);
		td.scale[1] = atof(token.string);

		//find default flags and values
		mt = FindMiptex (td.name);
		td.flags = textureref[mt].flags;
		td.value = textureref[mt].value;
		side->contents = textureref[mt].contents;
		side->surf = td.flags = textureref[mt].flags;

		//check if there's a number available
		if (PS_CheckTokenType(script, TT_NUMBER, 0, &token))
		{
			side->contents = token.intvalue;
			PS_ExpectTokenType(script, TT_NUMBER, 0, &token);
			side->surf = td.flags = token.intvalue;
			PS_ExpectTokenType(script, TT_NUMBER, 0, &token);
			td.value = token.intvalue;
		}

		// translucent objects are automatically classified as detail
		if (side->surf & (SURF_TRANS33|SURF_TRANS66) )
			side->contents |= CONTENTS_DETAIL;
		if (side->contents & (CONTENTS_PLAYERCLIP|CONTENTS_MONSTERCLIP) )
			side->contents |= CONTENTS_DETAIL;
		if (fulldetail)
			side->contents &= ~CONTENTS_DETAIL;
		if (!(side->contents & ((LAST_VISIBLE_CONTENTS-1) 
			| CONTENTS_PLAYERCLIP|CONTENTS_MONSTERCLIP|CONTENTS_MIST)  ) )
			side->contents |= CONTENTS_SOLID;

		// hints and skips are never detail, and have no content
		if (side->surf & (SURF_HINT|SURF_SKIP) )
		{
			side->contents = 0;
			side->surf &= ~CONTENTS_DETAIL;
		}

#ifdef ME
		//for creating AAS... this side is textured
		side->flags |= SFL_TEXTURED;
#endif //ME
		//
		// find the plane number
		//
		planenum = PlaneFromPoints (planepts[0], planepts[1], planepts[2]);
		if (planenum == -1)
		{
			Log_Print("Entity %i, Brush %i: plane with no normal\n"
				, b->entitynum, b->brushnum);
			continue;
		}

		//
		// see if the plane has been used already
		//
		for (k=0 ; k<b->numsides ; k++)
		{
			s2 = b->original_sides + k;
			if (s2->planenum == planenum)
			{
				Log_Print("Entity %i, Brush %i: duplicate plane\n"
					, b->entitynum, b->brushnum);
				break;
			}
			if ( s2->planenum == (planenum^1) )
			{
				Log_Print("Entity %i, Brush %i: mirrored plane\n"
					, b->entitynum, b->brushnum);
				break;
			}
		}
		if (k != b->numsides)
			continue;		// duplicated

		//
		// keep this side
		//

		side = b->original_sides + b->numsides;
		side->planenum = planenum;
		side->texinfo = TexinfoForBrushTexture (&mapplanes[planenum],
			&td, vec3_origin);

		// save the td off in case there is an origin brush and we
		// have to recalculate the texinfo
		side_brushtextures[nummapbrushsides] = td;

		nummapbrushsides++;
		b->numsides++;
	} while (1);

	// get the content for the entire brush
	b->contents = Q2_BrushContents (b);

#ifdef ME
	if (BrushExists(b))
	{
		c_squattbrushes++;
		b->numsides = 0;
		return;
	} //end if

	if (create_aas)
	{
		//create AAS brushes, and add brush bevels
		AAS_CreateMapBrushes(b, mapent, true);
		//NOTE: if we return here then duplicate plane errors occur for the non world entities
		return;
	} //end if
#endif //ME

	// allow detail brushes to be removed 
	if (nodetail && (b->contents & CONTENTS_DETAIL) )
	{
		b->numsides = 0;
		return;
	}

	// allow water brushes to be removed
	if (nowater && (b->contents & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER)) )
	{
		b->numsides = 0;
		return;
	}

	// create windings for sides and bounds for brush
	MakeBrushWindings (b);

	// brushes that will not be visible at all will never be
	// used as bsp splitters
	if (b->contents & (CONTENTS_PLAYERCLIP|CONTENTS_MONSTERCLIP) )
	{
		c_clipbrushes++;
		for (i=0 ; i<b->numsides ; i++)
			b->original_sides[i].texinfo = TEXINFO_NODE;
	}

	//
	// origin brushes are removed, but they set
	// the rotation origin for the rest of the brushes
	// in the entity.  After the entire entity is parsed,
	// the planenums and texinfos will be adjusted for
	// the origin brush
	//
	if (b->contents & CONTENTS_ORIGIN)
	{
		char	string[32];
		vec3_t	origin;

		if (num_entities == 1)
		{
			Error ("Entity %i, Brush %i: origin brushes not allowed in world"
				, b->entitynum, b->brushnum);
			return;
		}

		VectorAdd (b->mins, b->maxs, origin);
		VectorScale (origin, 0.5, origin);

		sprintf (string, "%i %i %i", (int)origin[0], (int)origin[1], (int)origin[2]);
		SetKeyValue (&entities[b->entitynum], "origin", string);

		VectorCopy (origin, entities[b->entitynum].origin);

		// don't keep this brush
		b->numsides = 0;

		return;
	}

	AddBrushBevels(b);

	nummapbrushes++;
	mapent->numbrushes++;		
}