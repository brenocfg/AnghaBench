#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  lines; TYPE_1__* display; } ;
struct TYPE_17__ {int /*<<< orphan*/  pid; } ;
struct TYPE_14__ {char** data; } ;
struct TYPE_16__ {int error; TYPE_10__ data; struct TYPE_16__* next; struct TYPE_16__* files; } ;
struct TYPE_15__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;
typedef  TYPE_2__ OpenFiles_ProcessData ;
typedef  TYPE_2__ OpenFiles_FileData ;
typedef  TYPE_4__ OpenFilesScreen ;
typedef  TYPE_5__ InfoScreen ;

/* Variables and functions */
 int /*<<< orphan*/  InfoScreen_addLine (TYPE_5__*,char*) ; 
 TYPE_2__* OpenFilesScreen_getProcessData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenFiles_Data_clear (TYPE_10__*) ; 
 int Panel_getSelectedIndex (TYPE_1__*) ; 
 int /*<<< orphan*/  Panel_prune (TYPE_1__*) ; 
 int /*<<< orphan*/  Panel_setSelected (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Vector_insertionSort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,char*,char*,char*,char*,char*,char*) ; 

void OpenFilesScreen_scan(InfoScreen* this) {
   Panel* panel = this->display;
   int idx = Panel_getSelectedIndex(panel);
   Panel_prune(panel);
   OpenFiles_ProcessData* pdata = OpenFilesScreen_getProcessData(((OpenFilesScreen*)this)->pid);
   if (pdata->error == 127) {
      InfoScreen_addLine(this, "Could not execute 'lsof'. Please make sure it is available in your $PATH.");
   } else if (pdata->error == 1) {
      InfoScreen_addLine(this, "Failed listing open files.");
   } else {
      OpenFiles_FileData* fdata = pdata->files;
      while (fdata) {
         char** data = fdata->data.data;
         int lenN = data['n'] ? strlen(data['n']) : 0;
         int sizeEntry = 5 + 7 + 10 + 10 + 10 + lenN + 5 /*spaces*/ + 1 /*null*/;
         char entry[sizeEntry];
         xSnprintf(entry, sizeEntry, "%5.5s %7.7s %10.10s %10.10s %10.10s %s",
            data['f'] ? data['f'] : "",
            data['t'] ? data['t'] : "",
            data['D'] ? data['D'] : "",
            data['s'] ? data['s'] : "",
            data['i'] ? data['i'] : "",
            data['n'] ? data['n'] : "");
         InfoScreen_addLine(this, entry);
         OpenFiles_Data_clear(&fdata->data);
         OpenFiles_FileData* old = fdata;
         fdata = fdata->next;
         free(old);
      }
      OpenFiles_Data_clear(&pdata->data);
   }
   free(pdata);
   Vector_insertionSort(this->lines);
   Vector_insertionSort(panel->items);
   Panel_setSelected(panel, idx);
}