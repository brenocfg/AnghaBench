#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ colorScheme; void* delay; void* accountGuestInCPUMeter; void* updateProcessNames; void* countCPUsFromZero; void* detailedCPUTime; void* headerMargin; void* highlightThreads; void* highlightMegabytes; void* highlightBaseName; void* showProgramPath; void* showThreadNames; void* shadowOtherUsers; void* hideUserlandThreads; void* hideKernelThreads; void* hideThreads; void* treeView; void* direction; void* sortKey; int /*<<< orphan*/  flags; int /*<<< orphan*/  fields; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_dropPrivileges () ; 
 int /*<<< orphan*/  CRT_restorePrivileges () ; 
 scalar_t__ LAST_COLORSCHEME ; 
 int /*<<< orphan*/  Settings_defaultMeters (TYPE_1__*) ; 
 int /*<<< orphan*/  Settings_readMeterModes (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  Settings_readMeters (TYPE_1__*,char*,int) ; 
 scalar_t__ String_eq (char*,char*) ; 
 int /*<<< orphan*/  String_freeArray (char**) ; 
 char* String_readLine (int /*<<< orphan*/ *) ; 
 char** String_split (char*,char,int*) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  readFields (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool Settings_read(Settings* this, const char* fileName) {
   FILE* fd;
   
   CRT_dropPrivileges();
   fd = fopen(fileName, "r");
   CRT_restorePrivileges();
   if (!fd)
      return false;
   
   bool didReadMeters = false;
   bool didReadFields = false;
   for (;;) {
      char* line = String_readLine(fd);
      if (!line) {
         break;
      }
      int nOptions;
      char** option = String_split(line, '=', &nOptions);
      free (line);
      if (nOptions < 2) {
         String_freeArray(option);
         continue;
      }
      if (String_eq(option[0], "fields")) {
         readFields(this->fields, &(this->flags), option[1]);
         didReadFields = true;
      } else if (String_eq(option[0], "sort_key")) {
         // This "+1" is for compatibility with the older enum format.
         this->sortKey = atoi(option[1]) + 1;
      } else if (String_eq(option[0], "sort_direction")) {
         this->direction = atoi(option[1]);
      } else if (String_eq(option[0], "tree_view")) {
         this->treeView = atoi(option[1]);
      } else if (String_eq(option[0], "hide_threads")) {
         this->hideThreads = atoi(option[1]);
      } else if (String_eq(option[0], "hide_kernel_threads")) {
         this->hideKernelThreads = atoi(option[1]);
      } else if (String_eq(option[0], "hide_userland_threads")) {
         this->hideUserlandThreads = atoi(option[1]);
      } else if (String_eq(option[0], "shadow_other_users")) {
         this->shadowOtherUsers = atoi(option[1]);
      } else if (String_eq(option[0], "show_thread_names")) {
         this->showThreadNames = atoi(option[1]);
      } else if (String_eq(option[0], "show_program_path")) {
         this->showProgramPath = atoi(option[1]);
      } else if (String_eq(option[0], "highlight_base_name")) {
         this->highlightBaseName = atoi(option[1]);
      } else if (String_eq(option[0], "highlight_megabytes")) {
         this->highlightMegabytes = atoi(option[1]);
      } else if (String_eq(option[0], "highlight_threads")) {
         this->highlightThreads = atoi(option[1]);
      } else if (String_eq(option[0], "header_margin")) {
         this->headerMargin = atoi(option[1]);
      } else if (String_eq(option[0], "expand_system_time")) {
         // Compatibility option.
         this->detailedCPUTime = atoi(option[1]);
      } else if (String_eq(option[0], "detailed_cpu_time")) {
         this->detailedCPUTime = atoi(option[1]);
      } else if (String_eq(option[0], "cpu_count_from_zero")) {
         this->countCPUsFromZero = atoi(option[1]);
      } else if (String_eq(option[0], "update_process_names")) {
         this->updateProcessNames = atoi(option[1]);
      } else if (String_eq(option[0], "account_guest_in_cpu_meter")) {
         this->accountGuestInCPUMeter = atoi(option[1]);
      } else if (String_eq(option[0], "delay")) {
         this->delay = atoi(option[1]);
      } else if (String_eq(option[0], "color_scheme")) {
         this->colorScheme = atoi(option[1]);
         if (this->colorScheme < 0 || this->colorScheme >= LAST_COLORSCHEME) this->colorScheme = 0;
      } else if (String_eq(option[0], "left_meters")) {
         Settings_readMeters(this, option[1], 0);
         didReadMeters = true;
      } else if (String_eq(option[0], "right_meters")) {
         Settings_readMeters(this, option[1], 1);
         didReadMeters = true;
      } else if (String_eq(option[0], "left_meter_modes")) {
         Settings_readMeterModes(this, option[1], 0);
         didReadMeters = true;
      } else if (String_eq(option[0], "right_meter_modes")) {
         Settings_readMeterModes(this, option[1], 1);
         didReadMeters = true;
      }
      String_freeArray(option);
   }
   fclose(fd);
   if (!didReadMeters) {
      Settings_defaultMeters(this);
   }
   return didReadFields;
}