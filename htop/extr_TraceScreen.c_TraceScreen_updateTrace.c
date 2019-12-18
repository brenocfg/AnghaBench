#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {int contLine; TYPE_2__ super; scalar_t__ follow; scalar_t__ tracing; int /*<<< orphan*/  strace; scalar_t__ fd_strace; } ;
typedef  TYPE_1__ TraceScreen ;
typedef  int /*<<< orphan*/  InfoScreen ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InfoScreen_addLine (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  InfoScreen_appendLine (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Panel_size (int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

void TraceScreen_updateTrace(InfoScreen* super) {
   TraceScreen* this = (TraceScreen*) super;
   char buffer[1001];
   fd_set fds;
   FD_ZERO(&fds);
// FD_SET(STDIN_FILENO, &fds);
   FD_SET(this->fd_strace, &fds);
   struct timeval tv;
   tv.tv_sec = 0; tv.tv_usec = 500;
   int ready = select(this->fd_strace+1, &fds, NULL, NULL, &tv);
   int nread = 0;
   if (ready > 0 && FD_ISSET(this->fd_strace, &fds))
      nread = fread(buffer, 1, 1000, this->strace);
   if (nread && this->tracing) {
      char* line = buffer;
      buffer[nread] = '\0';
      for (int i = 0; i < nread; i++) {
         if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (this->contLine) {
               InfoScreen_appendLine(&this->super, line);
               this->contLine = false;
            } else {
               InfoScreen_addLine(&this->super, line);
            }
            line = buffer+i+1;
         }
      }
      if (line < buffer+nread) {
         InfoScreen_addLine(&this->super, line);
         buffer[nread] = '\0';
         this->contLine = true;
      }
      if (this->follow)
         Panel_setSelected(this->super.display, Panel_size(this->super.display)-1);
   }
}