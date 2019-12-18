#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int direction; int hideThreads; int shadowOtherUsers; int showThreadNames; int hideKernelThreads; int hideUserlandThreads; int treeView; int highlightBaseName; int highlightMegabytes; int detailedCPUTime; int countCPUsFromZero; int updateProcessNames; int cpuCount; int showProgramPath; int highlightThreads; int* fields; char* filename; int changed; int headerMargin; int /*<<< orphan*/  delay; scalar_t__ colorScheme; int /*<<< orphan*/  flags; int /*<<< orphan*/  sortKey; } ;
typedef  TYPE_1__ Settings ;
typedef  int ProcessField ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_dropPrivileges () ; 
 int /*<<< orphan*/  CRT_restorePrivileges () ; 
 int /*<<< orphan*/  DEFAULT_DELAY ; 
 int /*<<< orphan*/  PERCENT_CPU ; 
 int* Platform_defaultFields ; 
 int Platform_numberOfFields ; 
 TYPE_6__* Process_fields ; 
 char const* SYSCONFDIR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Settings_defaultMeters (TYPE_1__*) ; 
 int Settings_read (TYPE_1__*,char*) ; 
 scalar_t__ Settings_write (TYPE_1__*) ; 
 void* String_cat (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* getenv (char*) ; 
 int lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 void* xCalloc (int,int) ; 
 void* xStrdup (char const*) ; 

Settings* Settings_new(int cpuCount) {
  
   Settings* this = xCalloc(1, sizeof(Settings));

   this->sortKey = PERCENT_CPU;
   this->direction = 1;
   this->hideThreads = false;
   this->shadowOtherUsers = false;
   this->showThreadNames = false;
   this->hideKernelThreads = false;
   this->hideUserlandThreads = false;
   this->treeView = false;
   this->highlightBaseName = false;
   this->highlightMegabytes = false;
   this->detailedCPUTime = false;
   this->countCPUsFromZero = false;
   this->updateProcessNames = false;
   this->cpuCount = cpuCount;
   this->showProgramPath = true;
   this->highlightThreads = true;
   
   this->fields = xCalloc(Platform_numberOfFields+1, sizeof(ProcessField));
   // TODO: turn 'fields' into a Vector,
   // (and ProcessFields into proper objects).
   this->flags = 0;
   ProcessField* defaults = Platform_defaultFields;
   for (int i = 0; defaults[i]; i++) {
      this->fields[i] = defaults[i];
      this->flags |= Process_fields[defaults[i]].flags;
   }

   char* legacyDotfile = NULL;
   char* rcfile = getenv("HTOPRC");
   if (rcfile) {
      this->filename = xStrdup(rcfile);
   } else {
      const char* home = getenv("HOME");
      if (!home) home = "";
      const char* xdgConfigHome = getenv("XDG_CONFIG_HOME");
      char* configDir = NULL;
      char* htopDir = NULL;
      if (xdgConfigHome) {
         this->filename = String_cat(xdgConfigHome, "/htop/htoprc");
         configDir = xStrdup(xdgConfigHome);
         htopDir = String_cat(xdgConfigHome, "/htop");
      } else {
         this->filename = String_cat(home, "/.config/htop/htoprc");
         configDir = String_cat(home, "/.config");
         htopDir = String_cat(home, "/.config/htop");
      }
      legacyDotfile = String_cat(home, "/.htoprc");
      
      CRT_dropPrivileges();
      (void) mkdir(configDir, 0700);
      (void) mkdir(htopDir, 0700);
      free(htopDir);
      free(configDir);
      struct stat st;
      int err = lstat(legacyDotfile, &st);
      if (err || S_ISLNK(st.st_mode)) {
         free(legacyDotfile);
         legacyDotfile = NULL;
      }
      CRT_restorePrivileges();
   }
   this->colorScheme = 0;
   this->changed = false;
   this->delay = DEFAULT_DELAY;
   bool ok = false;
   if (legacyDotfile) {
      ok = Settings_read(this, legacyDotfile);
      if (ok) {
         // Transition to new location and delete old configuration file
         if (Settings_write(this))
            unlink(legacyDotfile);
      }
      free(legacyDotfile);
   }
   if (!ok) {
      ok = Settings_read(this, this->filename);
   }
   if (!ok) {
      this->changed = true;
      // TODO: how to get SYSCONFDIR correctly through Autoconf?
      char* systemSettings = String_cat(SYSCONFDIR, "/htoprc");
      ok = Settings_read(this, systemSettings);
      free(systemSettings);
   }
   if (!ok) {
      Settings_defaultMeters(this);
      this->hideKernelThreads = true;
      this->highlightMegabytes = true;
      this->highlightThreads = true;
      this->headerMargin = true;
   }
   return this;
}