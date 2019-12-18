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
struct rusage {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
typedef  double sqlite3_int64 ;
struct TYPE_2__ {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 scalar_t__ enableTimer ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 double iBegin ; 
 int /*<<< orphan*/  printf (char*,double,double,double) ; 
 TYPE_1__ sBegin ; 
 double timeDiff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double timeOfDay () ; 

__attribute__((used)) static void endTimer(void){
  if( enableTimer ){
    sqlite3_int64 iEnd = timeOfDay();
    struct rusage sEnd;
    getrusage(RUSAGE_SELF, &sEnd);
    printf("Run Time: real %.3f user %f sys %f\n",
       (iEnd - iBegin)*0.001,
       timeDiff(&sBegin.ru_utime, &sEnd.ru_utime),
       timeDiff(&sBegin.ru_stime, &sEnd.ru_stime));
  }
}