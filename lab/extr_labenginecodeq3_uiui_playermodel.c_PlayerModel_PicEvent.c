#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int id; } ;
typedef  TYPE_7__ menucommon_s ;
struct TYPE_14__ {int /*<<< orphan*/  string; } ;
struct TYPE_13__ {int /*<<< orphan*/  string; } ;
struct TYPE_16__ {int modelpage; char** modelnames; int selectedmodel; TYPE_6__ skinname; TYPE_5__ modelname; int /*<<< orphan*/  modelskin; TYPE_4__* picbuttons; TYPE_2__* pics; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {TYPE_3__ generic; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {TYPE_1__ generic; } ;

/* Variables and functions */
 int ID_PLAYERPIC0 ; 
 scalar_t__ LOW_MEMORY ; 
 int MAX_MODELSPERPAGE ; 
 int PLAYERGRID_COLS ; 
 int PLAYERGRID_ROWS ; 
 int /*<<< orphan*/  PlayerModel_UpdateModel () ; 
 int /*<<< orphan*/  QMF_HIGHLIGHT ; 
 int /*<<< orphan*/  QMF_PULSEIFFOCUS ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Q_strupr (int /*<<< orphan*/ ) ; 
 TYPE_8__ s_playermodel ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ trap_MemoryRemaining () ; 

__attribute__((used)) static void PlayerModel_PicEvent( void* ptr, int event )
{
	int				modelnum;
	int				maxlen;
	char*			buffptr;
	char*			pdest;
	int				i;

	if (event != QM_ACTIVATED)
		return;

	for (i=0; i<PLAYERGRID_ROWS*PLAYERGRID_COLS; i++)
	{
		// reset
 		s_playermodel.pics[i].generic.flags       &= ~QMF_HIGHLIGHT;
 		s_playermodel.picbuttons[i].generic.flags |= QMF_PULSEIFFOCUS;
	}

	// set selected
	i = ((menucommon_s*)ptr)->id - ID_PLAYERPIC0;
	s_playermodel.pics[i].generic.flags       |= QMF_HIGHLIGHT;
	s_playermodel.picbuttons[i].generic.flags &= ~QMF_PULSEIFFOCUS;

	// get model and strip icon_
	modelnum = s_playermodel.modelpage*MAX_MODELSPERPAGE + i;
	buffptr  = s_playermodel.modelnames[modelnum] + strlen("models/players/");
	pdest    = strstr(buffptr,"icon_");
	if (pdest)
	{
		// track the whole model/skin name
		Q_strncpyz(s_playermodel.modelskin,buffptr,pdest-buffptr+1);
		strcat(s_playermodel.modelskin,pdest + 5);

		// separate the model name
		maxlen = pdest-buffptr;
		if (maxlen > 16)
			maxlen = 16;
		Q_strncpyz( s_playermodel.modelname.string, buffptr, maxlen );
		Q_strupr( s_playermodel.modelname.string );

		// separate the skin name
		maxlen = strlen(pdest+5)+1;
		if (maxlen > 16)
			maxlen = 16;
		Q_strncpyz( s_playermodel.skinname.string, pdest+5, maxlen );
		Q_strupr( s_playermodel.skinname.string );

		s_playermodel.selectedmodel = modelnum;

		if( trap_MemoryRemaining() > LOW_MEMORY ) {
			PlayerModel_UpdateModel();
		}
	}
}