#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ child; int /*<<< orphan*/  strace; } ;
typedef  TYPE_1__ TraceScreen ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  InfoScreen ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_enableDelay () ; 
 int /*<<< orphan*/  InfoScreen_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void TraceScreen_delete(Object* cast) {
   TraceScreen* this = (TraceScreen*) cast;
   if (this->child > 0) {
      kill(this->child, SIGTERM);
      waitpid(this->child, NULL, 0);
      fclose(this->strace);
   }
   CRT_enableDelay();
   free(InfoScreen_done((InfoScreen*)cast));
}