#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UsersTable ;
struct TYPE_27__ {int delay; scalar_t__ sortKey; scalar_t__ pidWhiteList; scalar_t__ treeView; int /*<<< orphan*/  useColors; int /*<<< orphan*/  userId; } ;
struct TYPE_26__ {int /*<<< orphan*/  height; } ;
struct TYPE_25__ {TYPE_2__* settings; int /*<<< orphan*/  cpuCount; } ;
struct TYPE_24__ {int delay; int treeView; scalar_t__ sortKey; int direction; scalar_t__ changed; int /*<<< orphan*/  colorScheme; } ;
struct TYPE_23__ {TYPE_4__* header; int /*<<< orphan*/ * panel; TYPE_3__* pl; int /*<<< orphan*/ * ut; TYPE_2__* settings; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Settings ;
typedef  int /*<<< orphan*/  ScreenManager ;
typedef  TYPE_3__ ProcessList ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  MainPanel ;
typedef  TYPE_4__ Header ;
typedef  TYPE_5__ CommandLineSettings ;

/* Variables and functions */
 int /*<<< orphan*/  COLORSCHEME_MONOCHROME ; 
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/ * CRT_colors ; 
 int /*<<< orphan*/  CRT_done () ; 
 int /*<<< orphan*/  CRT_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORIZONTAL ; 
 int /*<<< orphan*/  Hashtable_delete (scalar_t__) ; 
 int /*<<< orphan*/  Header_delete (TYPE_4__*) ; 
 TYPE_4__* Header_new (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Header_populateFromSettings (TYPE_4__*) ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ LINES ; 
 int /*<<< orphan*/ * MainPanel_new () ; 
 int /*<<< orphan*/  MainPanel_setState (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  MainPanel_updateTreeFunctions (int /*<<< orphan*/ *,int) ; 
 char* PROCDIR ; 
 int /*<<< orphan*/  Panel_getHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessList_delete (TYPE_3__*) ; 
 TYPE_3__* ProcessList_new (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessList_printHeader (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessList_scan (TYPE_3__*) ; 
 int /*<<< orphan*/  ProcessList_setPanel (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Process_setupColumnWidths () ; 
 size_t RESET_COLOR ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  ScreenManager_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ScreenManager_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ScreenManager_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ScreenManager_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Settings_delete (TYPE_2__*) ; 
 TYPE_2__* Settings_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Settings_write (TYPE_2__*) ; 
 int /*<<< orphan*/  UsersTable_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UsersTable_new () ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attron (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  millisleep (int) ; 
 int /*<<< orphan*/  mvhline (scalar_t__,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 TYPE_5__ parseArguments (int,char**) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char** argv) {

   char *lc_ctype = getenv("LC_CTYPE");
   if(lc_ctype != NULL)
      setlocale(LC_CTYPE, lc_ctype);
   else if ((lc_ctype = getenv("LC_ALL")))
      setlocale(LC_CTYPE, lc_ctype);
   else
      setlocale(LC_CTYPE, "");

   CommandLineSettings flags = parseArguments(argc, argv); // may exit()

#ifdef HAVE_PROC
   if (access(PROCDIR, R_OK) != 0) {
      fprintf(stderr, "Error: could not read procfs (compiled to look in %s).\n", PROCDIR);
      exit(1);
   }
#endif
   
   Process_setupColumnWidths();
   
   UsersTable* ut = UsersTable_new();
   ProcessList* pl = ProcessList_new(ut, flags.pidWhiteList, flags.userId);
   
   Settings* settings = Settings_new(pl->cpuCount);
   pl->settings = settings;

   Header* header = Header_new(pl, settings, 2);

   Header_populateFromSettings(header);

   if (flags.delay != -1)
      settings->delay = flags.delay;
   if (!flags.useColors) 
      settings->colorScheme = COLORSCHEME_MONOCHROME;
   if (flags.treeView)
      settings->treeView = true;

   CRT_init(settings->delay, settings->colorScheme);
   
   MainPanel* panel = MainPanel_new();
   ProcessList_setPanel(pl, (Panel*) panel);

   MainPanel_updateTreeFunctions(panel, settings->treeView);
      
   if (flags.sortKey > 0) {
      settings->sortKey = flags.sortKey;
      settings->treeView = false;
      settings->direction = 1;
   }
   ProcessList_printHeader(pl, Panel_getHeader((Panel*)panel));

   State state = {
      .settings = settings,
      .ut = ut,
      .pl = pl,
      .panel = (Panel*) panel,
      .header = header,
   };
   MainPanel_setState(panel, &state);
   
   ScreenManager* scr = ScreenManager_new(0, header->height, 0, -1, HORIZONTAL, header, settings, true);
   ScreenManager_add(scr, (Panel*) panel, -1);

   ProcessList_scan(pl);
   millisleep(75);
   ProcessList_scan(pl);

   ScreenManager_run(scr, NULL, NULL);   
   
   attron(CRT_colors[RESET_COLOR]);
   mvhline(LINES-1, 0, ' ', COLS);
   attroff(CRT_colors[RESET_COLOR]);
   refresh();
   
   CRT_done();
   if (settings->changed)
      Settings_write(settings);
   Header_delete(header);
   ProcessList_delete(pl);

   ScreenManager_delete(scr);
   
   UsersTable_delete(ut);
   Settings_delete(settings);
   
   if(flags.pidWhiteList) {
      Hashtable_delete(flags.pidWhiteList);
   }
   return 0;
}