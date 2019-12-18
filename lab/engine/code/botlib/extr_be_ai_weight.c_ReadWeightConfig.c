#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* filename; size_t numweights; TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_17__ {char* string; } ;
typedef  TYPE_3__ token_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_18__ {int /*<<< orphan*/ * child; int /*<<< orphan*/ * next; int /*<<< orphan*/  value; scalar_t__ index; } ;
typedef  TYPE_4__ fuzzyseperator_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_15__ {char* name; TYPE_4__* firstseperator; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOTFILESBASEFOLDER ; 
 int /*<<< orphan*/  FreeMemory (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeSource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeWeightConfig (TYPE_2__*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  LibVarGetValue (char*) ; 
 int /*<<< orphan*/ * LoadSourceFile (char*) ; 
 int /*<<< orphan*/  MAX_INVENTORYVALUE ; 
 size_t MAX_WEIGHTS ; 
 int MAX_WEIGHT_FILES ; 
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ PC_ReadToken (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PC_SetBaseFolder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 TYPE_4__* ReadFuzzySeperators_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadFuzzyWeight (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SourceWarning (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StripDoubleQuotes (char*) ; 
 int Sys_MilliSeconds () ; 
 int /*<<< orphan*/  TT_STRING ; 
 scalar_t__ botDeveloper ; 
 TYPE_6__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__** weightFileList ; 

weightconfig_t *ReadWeightConfig(char *filename)
{
	int newindent, avail = 0, n;
	token_t token;
	source_t *source;
	fuzzyseperator_t *fs;
	weightconfig_t *config = NULL;
#ifdef DEBUG
	int starttime;

	starttime = Sys_MilliSeconds();
#endif //DEBUG

	if (!LibVarGetValue("bot_reloadcharacters"))
	{
		avail = -1;
		for( n = 0; n < MAX_WEIGHT_FILES; n++ )
		{
			config = weightFileList[n];
			if( !config )
			{
				if( avail == -1 )
				{
					avail = n;
				} //end if
				continue;
			} //end if
			if( strcmp( filename, config->filename ) == 0 )
			{
				//botimport.Print( PRT_MESSAGE, "retained %s\n", filename );
				return config;
			} //end if
		} //end for

		if( avail == -1 )
		{
			botimport.Print( PRT_ERROR, "weightFileList was full trying to load %s\n", filename );
			return NULL;
		} //end if
	} //end if

	PC_SetBaseFolder(BOTFILESBASEFOLDER);
	source = LoadSourceFile(filename);
	if (!source)
	{
		botimport.Print(PRT_ERROR, "counldn't load %s\n", filename);
		return NULL;
	} //end if
	//
	config = (weightconfig_t *) GetClearedMemory(sizeof(weightconfig_t));
	config->numweights = 0;
	Q_strncpyz( config->filename, filename, sizeof(config->filename) );
	//parse the item config file
	while(PC_ReadToken(source, &token))
	{
		if (!strcmp(token.string, "weight"))
		{
			if (config->numweights >= MAX_WEIGHTS)
			{
				SourceWarning(source, "too many fuzzy weights");
				break;
			} //end if
			if (!PC_ExpectTokenType(source, TT_STRING, 0, &token))
			{
				FreeWeightConfig(config);
				FreeSource(source);
				return NULL;
			} //end if
			StripDoubleQuotes(token.string);
			config->weights[config->numweights].name = (char *) GetClearedMemory(strlen(token.string) + 1);
			strcpy(config->weights[config->numweights].name, token.string);
			if (!PC_ExpectAnyToken(source, &token))
			{
				FreeWeightConfig(config);
				FreeSource(source);
				return NULL;
			} //end if
			newindent = qfalse;
			if (!strcmp(token.string, "{"))
			{
				newindent = qtrue;
				if (!PC_ExpectAnyToken(source, &token))
				{
					FreeWeightConfig(config);
					FreeSource(source);
					return NULL;
				} //end if
			} //end if
			if (!strcmp(token.string, "switch"))
			{
				fs = ReadFuzzySeperators_r(source);
				if (!fs)
				{
					FreeWeightConfig(config);
					FreeSource(source);
					return NULL;
				} //end if
				config->weights[config->numweights].firstseperator = fs;
			} //end if
			else if (!strcmp(token.string, "return"))
			{
				fs = (fuzzyseperator_t *) GetClearedMemory(sizeof(fuzzyseperator_t));
				fs->index = 0;
				fs->value = MAX_INVENTORYVALUE;
				fs->next = NULL;
				fs->child = NULL;
				if (!ReadFuzzyWeight(source, fs))
				{
					FreeMemory(fs);
					FreeWeightConfig(config);
					FreeSource(source);
					return NULL;
				} //end if
				config->weights[config->numweights].firstseperator = fs;
			} //end else if
			else
			{
				SourceError(source, "invalid name %s", token.string);
				FreeWeightConfig(config);
				FreeSource(source);
				return NULL;
			} //end else
			if (newindent)
			{
				if (!PC_ExpectTokenString(source, "}"))
				{
					FreeWeightConfig(config);
					FreeSource(source);
					return NULL;
				} //end if
			} //end if
			config->numweights++;
		} //end if
		else
		{
			SourceError(source, "invalid name %s", token.string);
			FreeWeightConfig(config);
			FreeSource(source);
			return NULL;
		} //end else
	} //end while
	//free the source at the end of a pass
	FreeSource(source);
	//if the file was located in a pak file
	botimport.Print(PRT_MESSAGE, "loaded %s\n", filename);
#ifdef DEBUG
	if (botDeveloper)
	{
		botimport.Print(PRT_MESSAGE, "weights loaded in %d msec\n", Sys_MilliSeconds() - starttime);
	} //end if
#endif //DEBUG
	//
	if (!LibVarGetValue("bot_reloadcharacters"))
	{
		weightFileList[avail] = config;
	} //end if
	//
	return config;
}